#include "Solver.h"

#include <cstdlib>
#include <ctime>

Vec Solver::StartUp(const json& config)
{
	// read config
	{
		integrator	= config["sim"]["integrator"];
		h			= config["sim"]["stepSize"];
		numSubsteps = config["sim"]["numSubsteps"];
		interpolator = new Interpolator{ config };

		// load mesh
		{
			std::string meshPath = "../Media/vega/" + std::string{ config["sim"]["model"] } + ".veg";
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
			double E  = config["sim"]["material"]["E"];
			double nu = config["sim"]["material"]["nu"];
			rho		  = config["sim"]["material"]["rho"];
			const std::string energyName = config["sim"]["material"]["energyFunction"];
			if (energyName == "ARAP")
				energyFunction = new ARAP{ E, nu };
			else if (energyName == "SNH")
				energyFunction = new StableNeoHookean{ E, nu };
		}

		for(int i = 0; i < config["sim"]["BCs"].size(); ++i)
			BCs.push_back(config["sim"]["BCs"][i]);

		for (int i = 0; i < config["sim"]["loadCases"]["nodes"].size(); ++i)
			loadedVerts.push_back(config["sim"]["loadCases"]["nodes"][i]);

	}

	numVertices = mesh->getNumVertices();
	numDOFs = 3 * numVertices;
	numElements = mesh->getNumElements();

	x = Vec::Zero(numDOFs);
	v = Vec::Zero(numDOFs);
	fExt = Vec::Zero(numDOFs);

	//energyFunction = new ARAP{ 1'000'000, 0.35 };

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

	// create Keff
	{
		Keff = SpMat(numDOFs, numDOFs);
		for (int i = 0; i < numElements; ++i)
		{
			Vec3 v0, v1, v2, v3;
			int indices[4];
			{
				indices[0] = 3 * mesh->getVertexIndex(i, 0);
				indices[1] = 3 * mesh->getVertexIndex(i, 1);
				indices[2] = 3 * mesh->getVertexIndex(i, 2);
				indices[3] = 3 * mesh->getVertexIndex(i, 3);
			}

			Mat12 m;
			m.setZero();

			AddToKeff(Keff, m, &indices[0]);
		}
	}

	std::srand(std::time(nullptr)); // use current time as seed for random generator
	for (size_t i = 0; i < mesh->getNumVertices(); ++i)
	{
		/*
		x(3 * i + 0) = 10.0 * ((double)std::rand() / RAND_MAX - 0.5);
		x(3 * i + 1) = 10.0 * ((double)std::rand() / RAND_MAX - 0.5)+2.0;
		x(3 * i + 2) = 10.0 * ((double)std::rand() / RAND_MAX - 0.5);
		*/
		Vec3d v = mesh->getVertex(i);
		x(3 * i + 0) = v[0];
		x(3 * i + 1) = v[1];
		x(3 * i + 2) = v[2];

		/*
		Vec3d v = mesh->getVertex(i);
		x(3 * i + 0) = v[0];
		x(3 * i + 1) = 0.0;
		x(3 * i + 2) = v[2];

		x(3 * i + 0) = 0.0;
		x(3 * i + 1) = 0.0;
		x(3 * i + 2) = 0.0;
		*/
	}

	return x;
}

void Solver::ShutDown()
{
	delete mesh;
}

Vec Solver::Step()
{
	int substep = 0;

	/*
	double loadIncrement = 200.0;

	if(loadVal <= 50'000)
		loadVal += loadIncrement;
		
	if (stepNum > 200)
		loadVal = 0.0;

	for (auto index : loadedVerts)
		fExt(index) = loadVal;
	*/

	T += h;

	loadVal = interpolator->get(T);
	for (auto index : loadedVerts)
		fExt(index) = loadVal;

	std::cout << "T: " << T << "; fExt: " << loadVal << "; ";

	
	// clear Keff to 0.0
	for (int k = 0; k < Keff.outerSize(); ++k)
		for (Eigen::SparseMatrix<double>::InnerIterator it(Keff, k); it; ++it)
		{
			it.valueRef() = 0.0;
		}

	Vec fInt = Vec::Zero(numDOFs);
	for (;;)
	{
		PerformanceCounter jacobian;
		double dPdxTime = 0.0;
		double AddToKeffTime = 0.0;
		double FandPval = 0.0;
		for (int i = 0; i < numElements; ++i)
		{
			PerformanceCounter FandP;
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

				fEl *= -tetVols[i];
				//fEl *= -1.0;

				for (int el = 0; el < 4; ++el)
				{
					for (int incr = 0; incr < 3; ++incr)
					{
						fInt(indices[el] + incr) += fEl(3 * el + incr);
					}
				}
			}
			FandP.StopCounter();
			FandPval += FandP.GetElapsedTime();
			// get jacobian
			{
				PerformanceCounter dPdxCounter;
				Mat9x12 dFdx = dFdxs[i];
				Mat9 dPdF = energyFunction->GetJacobian();
				Mat12 dPdx = dFdx.transpose() * dPdF * dFdx;

				dPdx *= -tetVols[i];
				dPdxCounter.StopCounter();
				dPdxTime += dPdxCounter.GetElapsedTime();

				PerformanceCounter KeffCounter;
				AddToKeff(Keff, dPdx, &indices[0]);
				KeffCounter.StopCounter();
				AddToKeffTime += KeffCounter.GetElapsedTime();
			}
		}
		jacobian.StopCounter();
		std::cout << "jacobian filled in " << jacobian.GetElapsedTime() << ", F and P: " << FandPval 
			<< ", dPdx time: " << dPdxTime << " AddToKeffTime: " << AddToKeffTime << "; ";

		PerformanceCounter solution;
		//solve
		{
			if (integrator[0] == '0')
			{
				// backward euler
				// [ M - h * alpha * K - h^2 * K ] * dv = h * f + h^2 * K * v
				double h2 = h * h;
				double alpha = 0.01;
				double beta = 5.0;

				// h* f + h ^ 2 * K * v
				Vec RHS = h * ((fInt + fExt) + h * Keff * v);

				//M - h * alpha * K - h ^ 2 * K
				SpMat EffectiveMatrix = M - h * (alpha * Keff + beta * M) - h2 * Keff;

				// project constaints
				SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;
				Vec SystemVec = S * RHS;
				solver.compute(SystemMatrix);
				Vec dv = solver.solve(SystemVec);

				v.noalias() += dv;
				u = h * v;
				x.noalias() += u;
			}
			else if (integrator[0] == '1')
			{
				double factor = 1.0;
				SpMat EffectiveMatrix = Keff;
				SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;
				Vec SystemVec = S * (-fInt + fExt);
				//Vec SystemVec = S * ( -fInt - M*( u_0 * 0.000'001 ) );
				solver.compute(SystemMatrix);
				Vec u = solver.solve(SystemVec);
				x.noalias() += h * factor * u;
			}

			// quasistatic
			/*
			SpMat SystemMatrix = S * Keff * S + spI - S;
			Vec SystemVec = S * (-fInt + fExt);

			// project constaints
			solver.compute(SystemMatrix);
			Vec dv = solver.solve(SystemVec);
			x.noalias() += 0.01 * dv;
			*/

			// optimization
			/*
			h = 0.000'001;
			SpMat EffectiveMatrix = Keff;
			SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;
			Vec SystemVec = S * (-fInt+fExt);
			//Vec SystemVec = S * ( -fInt - M*( u_0 * 0.000'001 ) );
			solver.compute(SystemMatrix);
			Vec u = solver.solve(SystemVec);
			u_0 = u;
			x.noalias() += h * u;
			*/

			// optimization but with inertia
			/*
			// [ M - h * alpha * K - h^2 * K ] * dv = h * f + h^2 * K * v
			h = 0.001;
			double h2 = h * h;
			double alpha = 0.02;
			// h* f + h ^ 2 * K * v
			Vec RHS = h * ((-fInt) + h * Keff * v);

			//M - h * alpha * K - h ^ 2 * K
			//SpMat EffectiveMatrix = M - h * (alpha * Keff + M) - h2 * Keff;
			SpMat EffectiveMatrix = M - h * (alpha * Keff) - h2 * Keff;

			// project constaints
			SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;
			Vec SystemVec = S * RHS;
			solver.compute(SystemMatrix);
			Vec dv = solver.solve(SystemVec);

			v.noalias() += dv;
			u = h * v;
			x.noalias() += u;

			//R += fInt;
			
			h = 0.001;
			// [ M - h * alpha * K - h^2 * K ] * dv = h * f + h^2 * K * v
			double h2 = h * h;
			double alpha = 0.01;

			// h* f + h ^ 2 * K * v
			Vec RHS = h * ((fInt) + h * Keff * v);

			//M - h * alpha * K - h ^ 2 * K
			SpMat EffectiveMatrix = M - h * (alpha * Keff + M) - h2 * Keff;

			// project constaints
			//SpMat SystemMatrix = S * EffectiveMatrix * S + spI - S;
			//Vec SystemVec = S * RHS;
			solver.compute(EffectiveMatrix);
			Vec dv = solver.solve(RHS);

			v.noalias() += dv;
			u = h * v;
			x.noalias() += u;
			*/

		}
		solution.StopCounter();
		std::cout << "solved in " << solution.GetElapsedTime() << ' ';
		std::cout << "||f||^2= " << fInt.squaredNorm() << '\n';
		/*
		fInt = Vec::Zero(numDOFs);
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

				fEl *= -tetVols[i];
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
		
		double rR = R.norm();
		double rF = fExt.norm();
		double val = rR / rF;

		std::cout
			<< "stepNum: " << stepNum << " substep:" << substep++
			<< " rR / rF: " << val << ", t: " << T << ", f: " << loadVal << '\n';

		//if (val > 0.9 && val < 1.1)
		if(substep > 4)
			break;
		*/
		if(++substep > numSubsteps)
			break;
	}

	return x;
}

void Solver::AddToKeff(SpMat& Keff, const Mat12 & dPdx, int* indices)
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