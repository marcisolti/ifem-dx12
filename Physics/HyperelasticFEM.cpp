#include "HyperelasticFEM.h"

void HyperelasticFEM::Init(VolumetricMesh* mesh)
{

	this->mesh = mesh;

	numElements = mesh->getNumElements();
	numVertices = mesh->getNumVertices();
	numDOFs = 3 * numVertices;

	//solver.setTolerance(0.01);
	//solver.setMaxIterations(500);

	/*
	energyFunction = new StableNeoHookean{ 69e9, 0.3 };
	rho = 270'000;

	energyFunction = new StableNeoHookean{ 200'000, 0.45 };
	rho = 1000;
	*/

	energyFunction = new ARAP{ 200'000, 0.3 };
	rho = 1000;

	implicit = true;
	h = 0.01;
	//h = 0.000'000'001;

	// BCs, loaded verts, S, spI
	{
		std::vector<int> initBCs = { 
		/*
			1, 3, 6, 8, 11, 12, 13, 15,
			17, 18, 26, 29, 42, 45, 47,
			49, 58, 59, 60, 247, 248,
			256, 265 
		*/
		};

		loadedVerts =
		{
			3 * 296 + 1,
		};

		/*
		std::vector<int> initBCs = { 51,52,103,104,155,156,207,208 };
		loadedVerts =
		{
			3 * 0 + 2,
			3 * 52 + 2,
			3 * 104 + 2,
			3 * 156 + 2
		};
		*/
		/*
		std::vector<int> initBCs = { 1 };
		loadedVerts = { 3 * 4 + 1 };
		*/

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
			Mat3 Dm, DmInv;
			{
				Vec3d v0 = mesh->getVertex(i, 0);
				Vec3d v1 = mesh->getVertex(i, 1);
				Vec3d v2 = mesh->getVertex(i, 2);
				Vec3d v3 = mesh->getVertex(i, 3);

				Vec3d dm1 = v1 - v0;
				Vec3d dm2 = v2 - v0;
				Vec3d dm3 = v3 - v0;

				Dm <<
					dm1[0], dm2[0], dm3[0],
					dm1[1], dm2[1], dm3[1],
					dm1[2], dm2[2], dm3[2];

				DmInv = Dm.inverse();
			}		

			Mat9x12 dFdx = Mat9x12::Zero();
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
			}

			DmInvs.emplace_back(DmInv);
			dFdxs.emplace_back(dFdx);

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

	// init other vectors
	{
		x = Vec(numDOFs);
		for (int i = 0; i < numVertices; ++i)
		{
			Vec3d p = mesh->getVertex(i);
			//Vec3d p{ 0.0, 0.0, 0.0 };
			x(3 * i + 0) = p[0];
			x(3 * i + 1) = p[1];
			x(3 * i + 2) = p[2];
		}

		v = Vec::Zero(numDOFs);
		u = Vec::Zero(numDOFs);

	}
	
	R = Vec::Zero(numDOFs);
	fExt = Vec::Zero(numDOFs);
}

void HyperelasticFEM::Step(bool load)
{
	int substep = 0;
	static int stepNum = 0;

	static double loadVal = 0.0;
	double loadIncrement = -100.0;
	loadVal += loadIncrement;

	double rR, rF;
	Vec dv;

	R = Vec::Zero(numDOFs);
	for (auto index : loadedVerts)
	{
		fExt(index) += loadIncrement;
		R(index)    = -loadVal;
	}

	static double T = 0.0;
	T += h;

	for(;;)
	{
		// get Keff
		SpMat Keff = SpMat(numDOFs, numDOFs);
		//#pragma omp parallel for
		for (int i = 0; i < numElements; ++i)
		{
			Vec3 v0, v1, v2, v3;
			int indices[4];
			{
				indices[0] = 3 * mesh->getVertexIndex(i, 0);
				indices[1] = 3 * mesh->getVertexIndex(i, 1);
				indices[2] = 3 * mesh->getVertexIndex(i, 2);
				indices[3] = 3 * mesh->getVertexIndex(i, 3);

				v0 << x(indices[0] + 0), x(indices[0] + 1), x(indices[0] + 2);
				v1 << x(indices[1] + 0), x(indices[1] + 1), x(indices[1] + 2);
				v2 << x(indices[2] + 0), x(indices[2] + 1), x(indices[2] + 2);
				v3 << x(indices[3] + 0), x(indices[3] + 1), x(indices[3] + 2);
			}

			Mat3 F;
			{
				Vec3 ds1 = v1 - v0;
				Vec3 ds2 = v2 - v0;
				Vec3 ds3 = v3 - v0;

				Mat3 Ds;
				Ds <<
					ds1[0], ds2[0], ds3[0],
					ds1[1], ds2[1], ds3[1],
					ds1[2], ds2[2], ds3[2];
				Mat3 DmInv = DmInvs[i];
				F = Ds * DmInv;
			}

			Mat3 P = energyFunction->GetPK1(F);
			// get jacobian
			{

				Mat9x12 dFdx = dFdxs[i];
				Mat9 dPdF = energyFunction->GetJacobian();
				Mat12 dPdx = dFdx.transpose() * dPdF * dFdx;

				dPdx *= -tetVols[i];

				AddToKeff(Keff, dPdx, &indices[0]);
			}
		}

		//solve
		{
			// [ M - h * alpha * K - h^2 * K ] * dv = h * f + h^2 * K * v
			double h2 = h * h;
			double alpha = 0.02;

			// h* f + h ^ 2 * K * v
			//Vec RHS = h * f;
			Vec RHS = h * (-R + h * Keff * v);

			//M - h * alpha * K - h ^ 2 * K
			SpMat EffectiveMatrix = M - h * alpha * Keff - h2 * Keff;

			// project constaints
			SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;
			Vec SystemVec = S * RHS;

			solver.compute(SystemMatrix);
			Vec dv = solver.solve(SystemVec);

			v.noalias() += dv;
			u = h * v;
			x.noalias() += u;
		}
		
		Vec fInt = Vec::Zero(numDOFs);
		for (int i = 0; i < numElements; ++i)
		{
			Vec3 v0, v1, v2, v3;
			int indices[4];
			{
				indices[0] = 3 * mesh->getVertexIndex(i, 0);
				indices[1] = 3 * mesh->getVertexIndex(i, 1);
				indices[2] = 3 * mesh->getVertexIndex(i, 2);
				indices[3] = 3 * mesh->getVertexIndex(i, 3);

				v0 << x(indices[0] + 0), x(indices[0] + 1), x(indices[0] + 2);
				v1 << x(indices[1] + 0), x(indices[1] + 1), x(indices[1] + 2);
				v2 << x(indices[2] + 0), x(indices[2] + 1), x(indices[2] + 2);
				v3 << x(indices[3] + 0), x(indices[3] + 1), x(indices[3] + 2);
			}

			Mat3 F;
			{
				Vec3 ds1 = v1 - v0;
				Vec3 ds2 = v2 - v0;
				Vec3 ds3 = v3 - v0;

				Mat3 Ds;
				Ds <<
					ds1[0], ds2[0], ds3[0],
					ds1[1], ds2[1], ds3[1],
					ds1[2], ds2[2], ds3[2];
				Mat3 DmInv = DmInvs[i];
				F = Ds * DmInv;
			}

			Mat3 P = energyFunction->GetPK1(F);
			// calculate forces
			{
				Vec9 Pv = Flatten(P);
				Mat9x12 dFdx = dFdxs[i];
				Vec12 fEl;

				fEl = dFdx.transpose() * Pv;

				fEl *= tetVols[i];
				//fEl *= -1.0;

				for (int el = 0; el < 4; ++el)
				{
					for (int incr = 0; incr < 3; ++incr)
					{
						fInt(indices[el] + incr) += fEl(3 * el + incr);
					}
				}
			}
		}

		R = fInt - fExt;

		rR = R.norm();
		rF = fExt.norm();
		
		std::cout << rR << ' ' << rF << '\n';

		double val = rR / rF;

		std::cout 
			<< "stepNum: " << stepNum << " substep:" << substep++
			<< " rR / rF: " << val << ", t: " << T << ", f: " << loadVal << '\n';
		
		if (val > 0.9 && val < 1.1)
			break;
	}
	//} while (true);
	stepNum++;
}

void HyperelasticFEM::AddToKeff(SpMat& Keff, const Mat12& dPdx, int* indices)
{
	for (int x = 0; x < 4; ++x) 
	{
		for (int y = 0; y < 4; ++y)
		{
			for (int innerX = 0; innerX < 3; ++innerX) 
			{
				for (int innerY = 0; innerY < 3; ++innerY)
				{
					Keff.coeffRef(indices[x] + innerX, indices[y] + innerY) += dPdx(3 * x + innerX, 3 * y + innerY);
				}
			}
		}
	}
}
