#include "Simulator.h"

#include "Solver.h"
Solver solver;

void Simulator::StartUp(Renderer* renderer, json* config)
{
	this->config = config;
	stepNum = 0;
	const std::string path{ "../Media/vega/" };
	const std::string modelName = (*config)["sim"]["model"];
    renderer->AddDeformable(0, path + modelName + ".veg.obj");
    surfaceGeo = renderer->GetDeformableGeo();

	Vec initPos = solver.StartUp(config);

	numDOFs = 3 * surfaceGeo->vertices.size();
	
	posArray.push_back(initPos);
	stepNum++;
	(*config)["app"]["stepNum"] = stepNum;
	(*config)["app"]["displayIndex"] = 0;
}

void Simulator::ShutDown()
{
}

void Simulator::Step()
{
	Vec currPos = solver.Step();
	posArray.push_back(currPos);
	stepNum++;
	(*config)["app"]["stepNum"] = stepNum;
}

void Simulator::Update()
{
	int index = (*config)["app"]["displayIndex"];
	for (size_t i = 0; i < numDOFs / 3; ++i)
	{
		surfaceGeo->vertices[i].position.x = posArray[index](3 * i + 0);
		surfaceGeo->vertices[i].position.y = posArray[index](3 * i + 1);
		surfaceGeo->vertices[i].position.z = posArray[index](3 * i + 2);
	}


	// normal computation 
	std::vector<Float3> normals{ surfaceGeo->vertices.size(), { 0,0,0 } };
	for (uint32_t i = 0; i < surfaceGeo->indices.size() / 3; i += 3)
	{

		uint32_t index0 = surfaceGeo->indices[3 * i + 0];
		uint32_t index1 = surfaceGeo->indices[3 * i + 1];
		uint32_t index2 = surfaceGeo->indices[3 * i + 2];

		Float3 a = surfaceGeo->vertices[index0].position;
		Float3 b = surfaceGeo->vertices[index1].position;
		Float3 c = surfaceGeo->vertices[index2].position;

		Float3 ba = b - a;
		Float3 ca = c - a;

		Float3 cross = ba.Cross(ca);
		cross *= 0.5 / cross.Length();

		normals[index0] += cross;
		normals[index1] += cross;
		normals[index2] += cross;

	}

	// set normal data
	for (uint32_t i = 0; i < surfaceGeo->vertices.size(); ++i)
	{
		surfaceGeo->vertices[i].normal = normals[i];
	}


	surfaceGeo->SetData(
		reinterpret_cast<const void*>(&(surfaceGeo->vertices[0])),
		surfaceGeo->vertices.size() * sizeof(PNT_Vertex)
	);
}