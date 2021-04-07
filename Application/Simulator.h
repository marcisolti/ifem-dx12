#pragma once

#include "Renderer.h"

#include <string>

#include <Eigen/Dense>

#include "vega/volumetricMesh/volumetricMesh.h"
#include "vega/volumetricMesh/volumetricMeshLoader.h"
#include "vega/volumetricMesh/tetMesh.h"

using Vec = Eigen::VectorXd;

class Simulator
{
	GG::Geometry* surfaceGeo;
	VolumetricMesh* meshGeo;
	Vec u, initPos;
	std::vector<Vec> posArray;

public:
	Simulator() = default;
	~Simulator()= default;

	void StartUp(Renderer* renderer, const std::string& modelName);
	void ShutDown();

	void Step();
	void SetDisplayIndex(int index);
};

