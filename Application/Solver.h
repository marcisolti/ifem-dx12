#pragma once

#include <Eigen/Dense>

#include "vega/volumetricMesh/volumetricMesh.h"
#include "vega/volumetricMesh/volumetricMeshLoader.h"
#include "vega/volumetricMesh/tetMesh.h"

using Vec = Eigen::VectorXd;

class Solver
{
public:
	Solver() = default;
	~Solver() = default;

	void StartUp();
	void ShutDown();

	Vec* Step();
};

