#pragma once
#define NOMINMAX
#include "Renderer.h"

#include <string>
#include "Common/nlohmann/json.hpp"
using json = nlohmann::json;

#include "Solver.h"

class Simulator
{
	GG::Geometry* surfaceGeo;

	uint32_t numDOFs;
	int stepNum;

	json* config;

	Vec currentPos;

public:
	Simulator() = default;
	~Simulator()= default;

	void StartUp(Renderer* renderer, json* config);
	void ShutDown();

	void Step();
	void Update();
};