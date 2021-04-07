#pragma once

#include "Renderer.h"

#include <string>

#include "Solver.h"

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

