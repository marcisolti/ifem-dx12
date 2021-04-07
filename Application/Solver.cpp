#include "Solver.h"

void Solver::StartUp(const std::string& meshPath)
{
	std::cout << "loading mesh " << meshPath << '\n';

	mesh = VolumetricMeshLoader::load(meshPath.c_str());

	if (!mesh)
	{
		std::cout << "fail! terminating\n";
		std::exit(420);
	}
	else
	{
		std::cout << "success! num elements: "
			<< mesh->getNumElements()
			<< ";  num vertices: "
			<< mesh->getNumVertices() << ";\n";
	}

	numDOFs = 3 * mesh->getNumVertices();

	u = Vec::Zero(numDOFs);
	x = Vec::Zero(numDOFs);
	v = Vec::Zero(numDOFs);

	for (size_t i = 0; i < mesh->getNumVertices(); ++i)
	{
		Vec3d v = mesh->getVertex(i);
		x(3 * i + 0) = v[0];
		x(3 * i + 1) = v[1];
		x(3 * i + 2) = v[2];
	}
}

void Solver::ShutDown()
{
}

Vec Solver::Step()
{
	static float dt = 0.f;
	dt += 1.0 / 60;

	for (size_t i = 0; i < numDOFs / 3; ++i)
	{
		x(3 * i + 1) += dt / 5;
	}

	return x;
}
