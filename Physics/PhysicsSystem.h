#pragma once

#include <Egg/Common.h>

#include <GG/ConstantBuffer.hpp>
#include "RigidBody.h"

#include <map>
#include <string>

#include "physx/PxPhysicsAPI.h"
#include "physx/foundation/PxSimpleTypes.h"

using namespace physx;

namespace GG
{
	__declspec(align(256)) struct PerObjectCb {
		Float4x4 modelTransform;
		Float4x4 modelTransformInverse;
	};
}

__declspec(align(256)) struct PerObjectCb {
	GG::PerObjectCb data[1024];
};

class PxSystem
{

	// physx
	PxDefaultAllocator		gAllocator;
	PxDefaultErrorCallback	gErrorCallback;

	PxFoundation* gFoundation = nullptr;
	PxPhysics* gPhysics = nullptr;

	PxDefaultCpuDispatcher* gDispatcher = nullptr;
	PxScene* gScene = nullptr;

	PxReal mAccumulator = 0.0f;
	PxReal mStepSize = 1.0f / 60.0f;

	// physics system resources
	std::map<std::string, GG::RigidBody::P> rigidBodies;
	std::map<std::string, GG::AffineModifier::P> affineModifiers;
	GG::ConstantBuffer<PerObjectCb> perObjectCb;
	uint32_t objectCount;

public:
	PxSystem() : objectCount{ 0 } {  }
	
	void StartUp(ID3D12Device* device);

	void Update(float dt);

	void BindConstantBuffer(ID3D12GraphicsCommandList* commandList, const std::string& id)
	{
		commandList->SetGraphicsRootConstantBufferView(
			1, 
			perObjectCb.GetGPUVirtualAddress(rigidBodies[id]->index)
		);
	}

	GG::RigidBody::P GetRigidBody(const std::string& id) { return rigidBodies[id]; }

	void AddRigidBody(
		const std::string& id,
		const PxTransform& pose,
		const PxGeometry& geometry = PxSphereGeometry(1.f),
		bool kinematic = false,
		double sFriction = 0.5f,
		double dFriction = 0.5f,
		double rest = 0.6f
	) {

		GG::RigidBody::P rb = GG::RigidBody::Create(objectCount, gPhysics, gScene, pose, kinematic);

		PxMaterial* gMaterial = gPhysics->createMaterial(sFriction, dFriction, rest);
		PxShape* shape = gPhysics->createShape(geometry, *gMaterial, true);
		rb->AddShape(shape);
		shape->release();
		rb->Rotate({ 0,1,0 }, 3.141567 / 2);
		
		rigidBodies.insert({ id, rb });

		objectCount++;

	}

	void ScaleModifier(const std::string& id, float scale)
	{
		rigidBodies.at(id)->Scale(scale);
	}

	void RotationModifier(const std::string& id, Float3 axis, float angle)
	{
		rigidBodies.at(id)->Rotate(axis, angle);
	}

	void AddForce(const std::string& id, Float3 force) 
	{ 
		rigidBodies[id]->actor->addForce(~force);
	}

	void AddTorque(const std::string& id, Float3 torque)
	{
		rigidBodies[id]->actor->addTorque(~torque);
	}

};
