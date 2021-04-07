#include "Simulator.h"

#include "Solver.h"
Solver solver;

void Simulator::StartUp(Renderer* renderer, const std::string& modelName)
{
	std::string path{ "../Media/vega/" };
    renderer->AddDeformable(path + modelName + ".veg.obj");
    surfaceGeo = renderer->GetDeformableGeo();
	solver.StartUp(path + modelName + ".veg");

	numDOFs = 3 * surfaceGeo->vertices.size();
}

void Simulator::ShutDown()
{
}

void Simulator::Step()
{
	Vec currPos = solver.Step();
	posArray.push_back(currPos);
}

void Simulator::SetDisplayIndex(int index)
{
	for (size_t i = 0; i < numDOFs / 3; ++i)
	{
		surfaceGeo->vertices[i].position.x = posArray[index](3 * i + 0);
		surfaceGeo->vertices[i].position.y = posArray[index](3 * i + 1);
		surfaceGeo->vertices[i].position.z = posArray[index](3 * i + 2);
	}

	surfaceGeo->SetData(
		reinterpret_cast<const void*>(&(surfaceGeo->vertices[0])),
		surfaceGeo->vertices.size() * sizeof(PNT_Vertex)
	);
}