#include "Simulator.h"

void Simulator::StartUp(Renderer* renderer, const std::string& modelName)
{
    renderer->AddDeformable(modelName + ".veg.obj");
}

void Simulator::ShutDown()
{
}

void Simulator::Step()
{
}
