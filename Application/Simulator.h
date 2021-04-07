#pragma once

#include "Renderer.h"

#include <string>

#include "Solver.h"

class Simulator
{
	GG::Geometry* surfaceGeo;

	std::vector<Vec> posArray;

	uint32_t numDOFs;
	int stepNum;

public:
	Simulator() = default;
	~Simulator()= default;

	void StartUp(Renderer* renderer, const std::string& modelName);
	void ShutDown();

	void Step();
	void SetDisplayIndex(int index);
	int GetStepNum() { return stepNum; }
};

