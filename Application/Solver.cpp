#include "Solver.h"

#include <cstdlib>
#include <ctime>

Interpolator interpolator;

Vec Solver::StartUp(json* config)
{
	// read config
	{
		h			  = (*config)["sim"]["stepSize"];
		numSubsteps   = (*config)["sim"]["numSubsteps"];
		alpha		  = (*config)["sim"]["material"]["alpha"];
		beta		  = (*config)["sim"]["material"]["beta"];
		magicConstant = (*config)["sim"]["magicConstant"];

		interpolator.set(config);

		// load mesh
		{
			std::string meshPath = "../Media/vega/" + std::string{ (*config)["sim"]["model"] } + ".veg";
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
		}

		// set material
		{	
			double E					 = (*config)["sim"]["material"]["E"];
			double nu					 = (*config)["sim"]["material"]["nu"];
			const std::string energyName = (*config)["sim"]["material"]["energyFunction"];
			
			if (energyName == "ARAP")
			{
				energyFunction = new ARAP{ E, nu };
				lambda = nu * E / ((1.0 + nu) * (1.0 - 2.0 * nu)); // from vega fem homogeneousNeoHookeanIsotropicMaterial.cpp
				mu = E / (2.0 * (1.0 + nu));

				Twist[0].setZero();
				Twist[0](0, 1) = -1.0;
				Twist[0](1, 0) = 1.0;

				Twist[1].setZero();
				Twist[1](1, 2) = 1.0;
				Twist[1](2, 1) = -1.0;

				Twist[2].setZero();
				Twist[2](0, 2) = 1.0;
				Twist[2](2, 0) = -1.0;

				sq2inv = 1.0 / std::sqrt(2.0);
			}
			else if (energyName == "SNH")
				energyFunction = new StableNeoHookean{ E, nu };
		}

		for(int i = 0; i < (*config)["sim"]["BCs"].size(); ++i)
			BCs.push_back((*config)["sim"]["BCs"][i]);

		for (int i = 0; i < (*config)["sim"]["loadCases"]["nodes"].size(); ++i)
			loadedVerts.push_back((*config)["sim"]["loadCases"]["nodes"][i]);

		std::string integratorString = (*config)["sim"]["integrator"];
		if (integratorString == "qStatic")
			integrator = qStatic;
		else if (integratorString == "bwEuler")
			integrator = bwEuler;
		else if (integratorString == "Newmark")
			integrator = Newmark;
		else
			std::exit(420);
	}

	numVertices = mesh->getNumVertices();
	numDOFs = 3 * numVertices;
	numElements = mesh->getNumElements();

	T = 0.0;

	x.setZero(numDOFs);
	x_0.setZero(numDOFs);
	u.setZero(numDOFs);
	v.setZero(numDOFs);
	a.setZero(numDOFs);
	z.setZero(numDOFs);
	fExt.setZero(numDOFs);

	// BCs, loaded verts, S, spI
	{

		S = SpMat(numDOFs, numDOFs);
		spI = SpMat(numDOFs, numDOFs);

		S.setIdentity();
		spI.setIdentity();

		for (auto bc : BCs)
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

		double rho = (*config)["sim"]["material"]["rho"];
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

	// create Keff, tbb arrays
	{
		Keff = SpMat(numDOFs, numDOFs);

		for (int i = 0; i < numElements; ++i)
		{
			{
				indexArray.push_back(3 * mesh->getVertexIndex(i, 0));
				indexArray.push_back(3 * mesh->getVertexIndex(i, 1));
				indexArray.push_back(3 * mesh->getVertexIndex(i, 2));
				indexArray.push_back(3 * mesh->getVertexIndex(i, 3));
			}

			Mat12 m;
			m.setZero();

			AddToKeff(m, i);
		}

		fIntArray = std::vector<Vec12>{ numElements, Vec12::Zero() };
		KelArray  = std::vector<Mat12>{ numElements, Mat12::Zero() };

	}

	// set init position
	{
		std::srand(std::time(nullptr)); // use current time as seed for random generator

		std::string initConfig = (*config)["sim"]["initConfig"];
		for (size_t i = 0; i < mesh->getNumVertices(); ++i)
		{
			Vec3d v = mesh->getVertex(i);
			x(3 * i + 0) = v[0];
			x(3 * i + 1) = v[1];
			x(3 * i + 2) = v[2];
		}

		if (initConfig.at(0) == 'p')
		{
			for (size_t i = 0; i < mesh->getNumVertices(); ++i)
			{
				switch (initConfig.at(1))
				{
				case 'x':
					x(3 * i + 0) = 0.0;
					break;
				case 'y':
					x(3 * i + 1) = 0.0;
					break;
				case 'z':
					x(3 * i + 2) = 0.0;
					break;
				}
			}
		}

		if (initConfig.at(0) == 'o')
		{
			for (size_t i = 0; i < mesh->getNumVertices(); ++i)
			{
				Vec3d v = mesh->getVertex(i);
				x(3 * i + 0) = 0.0;
				x(3 * i + 1) = 0.0;
				x(3 * i + 2) = 0.0;
			}
		}
	}

	x_0 = x;
	return x;
}

void Solver::ShutDown()
{
	delete mesh;
}

Vec Solver::Step()
{
	int substep = 0;
	T += h;

	double loadValue = interpolator.get(T);
	for (auto index : loadedVerts)
	{
		fExt(index)  = loadValue;
	}

	std::cout << "T:" << T << ";\tfExt: " << loadValue << ";\t";

	// clear Keff to 0.0
	for (int k = 0; k < Keff.outerSize(); ++k)
		for (Eigen::SparseMatrix<double>::InnerIterator it(Keff, k); it; ++it)
			it.valueRef() = 0.0;

	fInt.setZero(numDOFs);
	for (;;)
	{
		// build Keff
		PerformanceCounter jacobian;
		for (int i = 0; i < numElements; i++)
			ComputeElementJacobianAndHessian(i);
		
		// accumulating Keff and fInt
		{
			// filling up fInt
			for (int i = 0; i < numElements; ++i)
			{
				int* indices = &(indexArray[4*i]);
				for (int el = 0; el < 4; ++el)
				{
					for (int incr = 0; incr < 3; ++incr)
					{
						fInt(indices[el] + incr) += fIntArray[i](3 * el + incr);
					}
				}
			}
			// filling up Keff
			for (int i = 0; i < numElements; ++i)
			{
				int* indices = &(indexArray[4*i]);
				for (int x = 0; x < 4; ++x)
				{
					for (int y = 0; y < 4; ++y)
					{
						for (int innerX = 0; innerX < 3; ++innerX)
						{
							for (int innerY = 0; innerY < 3; ++innerY)
							{
								Keff.coeffRef(indices[x] + innerX, indices[y] + innerY) += KelArray[i](3 * x + innerX, 3 * y + innerY);
							}
						}
					}
				}
			}

		}
		jacobian.StopCounter();
		std::cout << "\tbuilt Keff in " << jacobian.GetElapsedTime() << ";\t";

		PerformanceCounter solution;
		switch (integrator)
		{
		case qStatic:
		{
			// boundary condition projection
			SpMat SystemMatrix = S * Keff * S + spI - S;
			Vec SystemVec = S * (-fInt + fExt);

			solver.compute(SystemMatrix);
			Vec u = solver.solve(SystemVec);

			x.noalias() += h * magicConstant * u;
		}
		break;
		case bwEuler:
		{
			// backward euler
			// [ M - h * alpha * K - h^2 * K ] * dv = h * f + h^2 * K * v
			double h2 = h * h;

			// h* f + h ^ 2 * K * v
			Vec RHS = h * ((fInt + fExt) + h * Keff * v);

			//M - h * alpha * K - h ^ 2 * K
			SpMat EffectiveMatrix = M - h * (alpha * Keff + beta * M) - h2 * Keff;

			Vec SystemVec = S * RHS;

			// project constaints
			SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;

			solver.compute(SystemMatrix);
			Vec dv = solver.solve(SystemVec);

			v.noalias() += dv;
			u = h * v;
			x.noalias() += magicConstant * u;
		}
		break;
		case Newmark:
		{
			double h2Inv = 1.0 / (h * h);
			double hInv = 1.0 / h;

			SpMat C = alpha * Keff + beta * M;
			Vec RHS = fInt + fExt + M * (a + 4.0 * hInv * v + 4.0 * h2Inv * u) + C * (v + 2.0 * hInv * u);

			SpMat EffectiveMatrix = 4.0 * h2Inv * M + 2.0 * hInv * C + Keff;

			// project constaints
			Vec SystemVec = S * RHS;
			SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;

			solver.compute(SystemMatrix);
			Vec u_1 = solver.solve(SystemVec);

			Vec v_1 = 2.0 * hInv * (u_1 - u) - v;
			Vec a_1 = 4.0 * h2Inv * (u_1 - u) - 4.0 * hInv * v - a;

			u = u_1;
			v = v_1;
			a = a_1;

			x = x_0 + magicConstant * u;
		}
		break;
		}
		solution.StopCounter();
		std::cout << "solved in " << solution.GetElapsedTime() << '\n';
		/*
		r = fInt - fExt;
		double rNorm = r.squaredNorm();
		double fNorm = fExt.squaredNorm();
		double val = rNorm / fNorm;
		std::cout << "f: " << fNorm << " r:" << rNorm << " r/f: " << val <<'\n';
		*/
		if(++substep >= numSubsteps)
			break;
	}

	return x;
}

void Solver::ComputeElementJacobianAndHessian(int i)
{
	const int* indices = &(indexArray[4 * i]);

	Vec3 v0, v1, v2, v3;
	{
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

	Mat3 P, U, V, R;
	Vec3 Sigma;
	{
		using namespace Eigen;
		JacobiSVD<Mat3> SVD(F, ComputeFullU | ComputeFullV);
		Sigma = SVD.singularValues();
		U = SVD.matrixU();
		V = SVD.matrixV();

		R = U * V.transpose();
		P = mu * (F - R);
	}
	// calculate forces
	{
		Vec9 Pv = Flatten(P);
		Mat9x12 dFdx = dFdxs[i];

		Vec12 fEl = dFdx.transpose() * Pv;
		fEl *= -tetVols[i];

		fIntArray[i] = fEl;
	}
	// get jacobian
	{
		Mat9 dPdF;
		{
			double eigenLambda[3];
			eigenLambda[0] = 2.0 / (Sigma(0) + Sigma(1));
			eigenLambda[1] = 2.0 / (Sigma(1) + Sigma(2));
			eigenLambda[2] = 2.0 / (Sigma(0) + Sigma(2));

			if (Sigma(0) + Sigma(1) < 2.0)
				eigenLambda[0] = 1.0;

			if (Sigma(1) + Sigma(2) < 2.0)
				eigenLambda[1] = 1.0;

			if (Sigma(0) + Sigma(2) < 2.0)
				eigenLambda[2] = 1.0;

			Vec9 Q[3];
			for (int el = 0; el < 3; ++el)
				Q[el] = Flatten(sq2inv * U * Twist[el] * V.transpose());

			dPdF.setIdentity();
			for (int el = 0; el < 3; ++el)
				dPdF -= eigenLambda[el] * Q[el] * Q[el].transpose();
			dPdF *= 2.0;
		}

		Mat9x12 dFdx = dFdxs[i];
		Mat12 dPdx = dFdx.transpose() * dPdF * dFdx;
		dPdx *= -tetVols[i];

		KelArray[i] = dPdx;
	}

}

void Solver::AddToKeff(const Mat12& dPdx, int elem)
{
	int* indices = &(indexArray[4*elem]);
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