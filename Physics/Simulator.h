#pragma once

#include <Egg/Common.h>

#include <GG/RenderingSystem.h>
//#include "Geometry.h"

#include "PhysicsSystem.h"
#include "SerialObjLoader.h"

#include <cmath>

struct Input {
	bool load;
};

class Simulator
{
	std::string id;
	std::vector<uint32_t> indices;
	std::vector<PNT_Vertex> initVertices;
	float T;

public:

	Simulator() {  }

	void Update(RenderingSystem* renderer, float dt, bool load);

	void AddDeformableMesh(
		RenderingSystem* renderer,
		PxSystem* physics,
		const std::string& id,
		ID3D12Device* device,
		const std::string& geoPath,
		const std::string& meshPath
	);

};