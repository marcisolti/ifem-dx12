#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>

#include "vega/volumetricMesh/volumetricMesh.h"
#include "vega/volumetricMesh/volumetricMeshLoader.h"
#include "vega/volumetricMesh/tetMesh.h"

#include "EnergyFunction.h"
#include "Common/nlohmann/json.hpp"
using json = nlohmann::json;

#include "PerformanceCounter.h"

using Vec   = Eigen::VectorXd;
using SpMat = Eigen::SparseMatrix<double>;

struct loadVal
{
	double t, f;
};

class Interpolator
{
	std::vector<loadVal> vals;
	int step = 0;
public:
	Interpolator(const json& config)
	{
		for (int i = 0; i < config["sim"]["loadCases"]["loadSteps"].size(); ++i)
		{
			loadVal val;
			val.t = config["sim"]["loadCases"]["loadSteps"][i]["t"];
			val.f = config["sim"]["loadCases"]["loadSteps"][i]["f"];
			vals.push_back(val);
		}
		for (auto val : vals)
			std::cout << val.t << ' ' << val.f << '\n';
	}
	double get(double T)
	{
		int i = 0;
		//while (false) {
		while (vals[ i + 1 ].t < T) {
			if (i < vals.size())
			{
				i++;
			}
		}
		double t0 = vals[ i ].t;
		double f0 = vals[ i ].f;

		double t1 = vals[ i + 1 ].t;
		double f1 = vals[ i + 1 ].f;

		return f0 + (T - t0) * ((f1 - f0) / (t1 - t0));
	}
};

class Solver
{
	std::string integrator;
	EnergyFunction* energyFunction;
	double T = 0.01, h;
	int stepNum = 0.0;

	Interpolator* interpolator;

	VolumetricMesh* mesh;
	uint32_t numDOFs, numElements, numVertices;
	double rho;

	std::vector<int> loadedVerts, BCs;
	double loadVal;
	SpMat S;
	
	SpMat Keff, M, spI;
	Vec u, x, v, fExt;

	std::vector<double> tetVols;
	std::vector<Mat3> DmInvs;
	std::vector<Mat9x12> dFdxs;

	Eigen::ConjugateGradient<SpMat, Eigen::Lower | Eigen::Upper> solver;

public:
	
	Solver() = default;
	~Solver() = default;

	Vec StartUp(const json& config);
	void ShutDown();

	Vec Step();

private:

	void AddToKeff(SpMat& Keff, const Mat12& dPdx, int* indices);

	Mat3	ComputeDm(int i);
	Mat9x12 ComputedFdx(Mat3 DmInv);

};

