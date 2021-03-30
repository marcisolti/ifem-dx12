#include "PhysicsSystem.h"

void PxSystem::StartUp(ID3D12Device* device)
{
	perObjectCb.CreateResources(device, sizeof(GG::PerObjectCb));

	gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, nullptr);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -12.f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);
}

void PxSystem::Update(float dt)
{
	mAccumulator += dt;
	if (mAccumulator > mStepSize)
	{
		mAccumulator -= mStepSize;

		gScene->simulate(mStepSize);
		gScene->fetchResults(true);

		for (const auto& [id, rb] : rigidBodies)
		{
			rb->Update(dt);
			perObjectCb->data[rb->index].modelTransform = rb->GetModelMatrix();
			perObjectCb->data[rb->index].modelTransformInverse = rb->GetModelMatrixInverse();
		}
		perObjectCb.Upload();
	}
}
