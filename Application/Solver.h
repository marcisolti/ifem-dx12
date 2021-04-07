#pragma once

#include <Eigen/Dense>

#include "vega/volumetricMesh/volumetricMesh.h"
#include "vega/volumetricMesh/volumetricMeshLoader.h"
#include "vega/volumetricMesh/tetMesh.h"

using Vec = Eigen::VectorXd;

class Solver
{
	VolumetricMesh* mesh;

	uint32_t numDOFs;

	Vec u, x, v;

public:
	Solver() = default;
	~Solver() = default;

	void StartUp(const std::string& meshPath);
	void ShutDown();

	Vec Step();
};

