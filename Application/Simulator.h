#pragma once

#include "Renderer.h"

#include <string>

#include <Eigen/Dense>

using Vec = Eigen::VectorXd;

class Simulator
{
	Vec u;

public:
	Simulator() = default;
	~Simulator()= default;

	void StartUp(Renderer* renderer, const std::string& modelName);
	void ShutDown();

	void Step();
};

