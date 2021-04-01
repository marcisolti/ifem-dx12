#pragma once

#include <Eigen/Dense>

using Vec = Eigen::VectorXd;

class Simulator
{
	Vec u;

public:
	Simulator() = default;
	~Simulator()= default;

	void StartUp();
	void ShutDown();

	void Step();
};

