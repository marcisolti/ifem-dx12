#pragma once

#include "../vega/volumetricMesh/volumetricMesh.h"
#include "../vega/volumetricMesh/volumetricMeshLoader.h"
#include "../vega/volumetricMesh/tetMesh.h"

//#define EIGEN_USE_MKL_ALL
//#include <Eigen/PardisoSupport>

#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/IterativeLinearSolvers>
#include <Eigen/SVD>

#include "EnergyFunction.h"

typedef Eigen::SparseMatrix<double>   SpMat;
typedef Eigen::VectorXd				  Vec;
typedef Eigen::Triplet<double>		  T;

#include <iostream>
#include <vector>

class HyperelasticFEM
{
	EnergyFunction* energyFunction;

	bool implicit;
	double h;
	double rho;

	VolumetricMesh* mesh;
	uint32_t numElements;
	uint32_t numVertices;
	uint32_t numDOFs;

	std::vector<double> tetVols;
	std::vector<Mat3> DmInvs;
	std::vector<Mat9x12> dFdxs;

	std::vector<int> loadedVerts;

	SpMat M;
	SpMat S;
	SpMat spI;

	Vec v;
	Vec R;
	Vec fExt;

	Eigen::ConjugateGradient<SpMat, Eigen::Lower | Eigen::Upper> solver;
	//Eigen::SparseLU<SpMat> solver;
	//Eigen::PardisoLDLT<SpMat> solver;

	void AddToKeff(SpMat& Keff, const Mat12& dPdx, int* indices);

public:

	Vec x, u;

	HyperelasticFEM() {  }

	void Init(VolumetricMesh* mesh);
	void Step(bool load);

};