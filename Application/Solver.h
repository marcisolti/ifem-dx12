#pragma once

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>

#include "vega/volumetricMesh/volumetricMesh.h"
#include "vega/volumetricMesh/volumetricMeshLoader.h"
#include "vega/volumetricMesh/tetMesh.h"

#include "EnergyFunction.h"
#include "Integrator.h"

using Vec   = Eigen::VectorXd;
using SpMat = Eigen::SparseMatrix<double>;

class Solver
{
	EnergyFunction* energyFunction;
	Integrator*		integrator;

	VolumetricMesh* mesh;

	uint32_t numDOFs, numElements, numVertices;

	Vec u, x, v, fExt, R;

	std::vector<double> tetVols;
	std::vector<Mat3> DmInvs;
	std::vector<Mat9x12> dFdxs;

	double rho, h;

	std::vector<int> loadedVerts;

	SpMat M, S, spI;

	Eigen::ConjugateGradient<SpMat, Eigen::Lower | Eigen::Upper> solver;

public:
	
	Solver() = default;
	~Solver() = default;

	void StartUp(const std::string& meshPath);
	void ShutDown();

	Vec Step();

private:

	Mat3	ComputeDm(int i);
	Mat9x12 ComputedFdx(Mat3 DmInv);
	void AddToKeff(SpMat& Keff, const Mat12& dPdx, int* indices);

};

