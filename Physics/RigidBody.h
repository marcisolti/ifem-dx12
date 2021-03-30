#pragma once

#include <Egg/Common.h>
#include <Egg/Math/Math.h>

#include "PxHelper.h"

using namespace Egg::Math;
using namespace physx;

namespace GG
{
	GG_CLASS(AffineModifier)

	public:

	GG_ENDCLASS

	GG_CLASS(RigidBody)

		Float4x4 modelMatrix;
		Float4x4 modifierMatrix;
		Float3 position;

	public:

		int index;
		PxRigidDynamic* actor;

		RigidBody(int index, PxPhysics* gPhysics, PxScene* gScene, PxTransform pose, bool kinematic = false)
			: index{ index }
		{
			actor = gPhysics->createRigidDynamic(pose);
			actor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, kinematic);
			gScene->addActor(*actor);
		}

		void AddShape(PxShape* shape) { actor->attachShape(*shape); }

		void Scale(float scale) { modifierMatrix *= Float4x4::Scaling(Float3{ scale }); }
		void Rotate(Float3 axis, float angle) { modifierMatrix *= Float4x4::Rotation(axis, angle); }
		void Translate(Float3 t) { modifierMatrix *= Float4x4::Translation(t); }

		void Update(float dt)
		{
			PxTransform m = actor->getGlobalPose();

			float angle;
			Float3 axis;
			toRadiansAndUnitAxis(m.q, angle, ~axis);
			
			position = ~m.p;
			modelMatrix = modifierMatrix * Float4x4::Rotation(axis, angle) * Float4x4::Translation(position);
		}

		Float3   GetPosition()    { return position; }
		Float4x4 GetModelMatrix() { return modelMatrix; }
		Float4x4 GetModelMatrixInverse() { return modelMatrix.Invert(); }

	GG_ENDCLASS
}