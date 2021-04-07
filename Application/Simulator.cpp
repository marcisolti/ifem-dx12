#include "Simulator.h"

#include "Solver.h"
Solver solver;

void Simulator::StartUp(Renderer* renderer, const std::string& modelName)
{
	std::string path{ "../Media/vega/" };
    renderer->AddDeformable(path + modelName + ".veg.obj");
    surfaceGeo = renderer->GetDeformableGeo();

	std::cout << "loading mesh " << modelName << '\n';

	meshGeo = VolumetricMeshLoader::load(
		(std::string{ path + modelName + ".veg" }).c_str()
	);

	if (!meshGeo)
	{
		std::cout << "fail! terminating\n";
		std::exit(420);
	}
	else
	{
		std::cout << "success! num elements: "
			<< meshGeo->getNumElements()
			<< ";  num vertices: "
			<< meshGeo->getNumVertices() << ";\n";
	}

	u = Vec::Zero(3 * surfaceGeo->vertices.size());
	initPos = Vec::Zero(3 * surfaceGeo->vertices.size());

	for (size_t i = 0; i < meshGeo->getNumVertices(); ++i)
	{
		Vec3d v = meshGeo->getVertex(i);
		initPos(3 * i + 0) = v[0];
		initPos(3 * i + 1) = v[1];
		initPos(3 * i + 2) = v[2];
	}
}

void Simulator::ShutDown()
{
}

void Simulator::Step()
{
	static float dt = 0.f;
	dt += 1.0 / 60;

	Vec currPos = Vec::Zero(3 * meshGeo->getNumVertices());

	for (size_t i = 0; i < meshGeo->getNumVertices(); ++i)
	{
		u(3 * i + 1) = std::sin(initPos(3 * i + 0) + dt);
	}

	for (size_t i = 0; i < meshGeo->getNumVertices(); ++i)
	{
		currPos(3 * i + 0) = initPos(3 * i + 0) + u(3 * i + 0);
		currPos(3 * i + 1) = initPos(3 * i + 1) + u(3 * i + 1);
		currPos(3 * i + 2) = initPos(3 * i + 2) + u(3 * i + 2);
	}

	posArray.push_back(currPos);
}

void Simulator::SetDisplayIndex(int index)
{
	for (size_t i = 0; i < meshGeo->getNumVertices(); ++i)
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