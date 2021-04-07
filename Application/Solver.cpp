#include "Solver.h"

void Solver::StartUp(const std::string& meshPath)
{
	std::cout << "loading mesh " << meshPath << '\n';

	mesh = VolumetricMeshLoader::load(meshPath.c_str());

	if (!mesh)
	{
		std::cout << "fail! terminating\n";
		std::exit(420);
	}
	else
	{
		std::cout << "success! num elements: "
			<< mesh->getNumElements()
			<< ";  num vertices: "
			<< mesh->getNumVertices() << ";\n";
	}

	numVertices = mesh->getNumVertices();
	numDOFs = 3 * numVertices;
	numElements = mesh->getNumElements();

	u = Vec::Zero(numDOFs);
	x = Vec::Zero(numDOFs);
	v = Vec::Zero(numDOFs);

	for (size_t i = 0; i < mesh->getNumVertices(); ++i)
	{
		Vec3d v = mesh->getVertex(i);
		x(3 * i + 0) = v[0];
		x(3 * i + 1) = v[1];
		x(3 * i + 2) = v[2];
	}

	integrator = new Integrator;
	energyFunction = new ARAP{ 200'000, 0.3 };
	rho = 1000;

	h = 0.01;

	// BCs, loaded verts, S, spI
	{
		std::vector<int> initBCs = {
			1, 3, 6, 8, 11, 12, 13, 15,
			17, 18, 26, 29, 42, 45, 47,
			49, 58, 59, 60, 247, 248,
			256, 265
		};

		loadedVerts =
		{
			3 * 296 + 1,
		};

		S = SpMat(numDOFs, numDOFs);
		spI = SpMat(numDOFs, numDOFs);

		S.setIdentity();
		spI.setIdentity();

		for (auto bc : initBCs)
		{
			int index = 3 * (bc - 1);
			S.coeffRef(index + 0, index + 0) = 0.0;
			S.coeffRef(index + 1, index + 1) = 0.0;
			S.coeffRef(index + 2, index + 2) = 0.0;
		}
	}

	// DmInv, dFdx, mass
	{
		DmInvs.reserve(numElements);
		dFdxs.reserve(numElements);
		tetVols.reserve(numElements);

		M = SpMat(numDOFs, numDOFs);

		for (int i = 0; i < numElements; ++i)
		{
			Mat3 Dm = ComputeDm(i);
			
			Mat3 DmInv = Dm.inverse();
			DmInvs.emplace_back(DmInv);

			Mat9x12 dFdx = ComputedFdx(DmInv);
			dFdxs.emplace_back(dFdx);

			// tetVols, M mx.
			{
				double vol = std::abs((1.0 / 6) * Dm.determinant());
				tetVols.emplace_back(vol);
				double mass = rho * vol;
				for (int v = 0; v < 4; ++v)
				{
					int index = mesh->getVertexIndex(i, v);
					//std::cout << i << ',' << v << ':' << index << '\n';
					M.coeffRef(3 * index + 0, 3 * index + 0) += mass;
					M.coeffRef(3 * index + 1, 3 * index + 1) += mass;
					M.coeffRef(3 * index + 2, 3 * index + 2) += mass;
				}
			}

		}
	}
}

void Solver::ShutDown()
{
	delete mesh;
}

Vec Solver::Step()
{
	static float dt = 0.f;
	dt += 1.0 / 60;

	for (size_t i = 0; i < numDOFs / 3; ++i)
	{
		x(3 * i + 1) += dt / 5;
	}

	return x;
}

Mat3 Solver::ComputeDm(int i)
{
	Vec3d v0 = mesh->getVertex(i, 0);
	Vec3d v1 = mesh->getVertex(i, 1);
	Vec3d v2 = mesh->getVertex(i, 2);
	Vec3d v3 = mesh->getVertex(i, 3);

	Vec3d dm1 = v1 - v0;
	Vec3d dm2 = v2 - v0;
	Vec3d dm3 = v3 - v0;

	Mat3 Dm;
	Dm.setZero();
	Dm <<
		dm1[0], dm2[0], dm3[0],
		dm1[1], dm2[1], dm3[1],
		dm1[2], dm2[2], dm3[2];

	return Dm;
}

Mat9x12 Solver::ComputedFdx(Mat3 DmInv)
{
	const double m = DmInv(0, 0);
	const double n = DmInv(0, 1);
	const double o = DmInv(0, 2);
	const double p = DmInv(1, 0);
	const double q = DmInv(1, 1);
	const double r = DmInv(1, 2);
	const double s = DmInv(2, 0);
	const double t = DmInv(2, 1);
	const double u = DmInv(2, 2);

	const double t1 = -m - p - s;
	const double t2 = -n - q - t;
	const double t3 = -o - r - u;

	Mat9x12 dFdx;
	dFdx.setZero();

	dFdx(0, 0) = t1;
	dFdx(0, 3) = m;
	dFdx(0, 6) = p;
	dFdx(0, 9) = s;
	dFdx(1, 1) = t1;
	dFdx(1, 4) = m;
	dFdx(1, 7) = p;
	dFdx(1, 10) = s;
	dFdx(2, 2) = t1;
	dFdx(2, 5) = m;
	dFdx(2, 8) = p;
	dFdx(2, 11) = s;
	dFdx(3, 0) = t2;
	dFdx(3, 3) = n;
	dFdx(3, 6) = q;
	dFdx(3, 9) = t;
	dFdx(4, 1) = t2;
	dFdx(4, 4) = n;
	dFdx(4, 7) = q;
	dFdx(4, 10) = t;
	dFdx(5, 2) = t2;
	dFdx(5, 5) = n;
	dFdx(5, 8) = q;
	dFdx(5, 11) = t;
	dFdx(6, 0) = t3;
	dFdx(6, 3) = o;
	dFdx(6, 6) = r;
	dFdx(6, 9) = u;
	dFdx(7, 1) = t3;
	dFdx(7, 4) = o;
	dFdx(7, 7) = r;
	dFdx(7, 10) = u;
	dFdx(8, 2) = t3;
	dFdx(8, 5) = o;
	dFdx(8, 8) = r;
	dFdx(8, 11) = u;

	return dFdx;
}