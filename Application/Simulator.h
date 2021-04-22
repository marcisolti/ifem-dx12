#pragma once

#include "Renderer.h"

#include <string>
#include "Common/nlohmann/json.hpp"
using json = nlohmann::json;

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

	void StartUp(Renderer* renderer, const json& config);
	void ShutDown();

	void Step();
	void SetDisplayIndex(int index);
	int GetStepNum() { return stepNum; }
};

