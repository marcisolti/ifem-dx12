#pragma once

#include <Egg/Math/Math.h>
#include "physx/PxPhysicsAPI.h"

inline const physx::PxVec3& operator~(const Egg::Math::Float3& v)
{
	return *(const physx::PxVec3*)&v;
}
inline physx::PxVec3& operator~(Egg::Math::Float3& v)
{
	return *(physx::PxVec3*)&v;
}

inline const physx::PxQuat& operator~(const Egg::Math::Float4& v)
{
	return *(const physx::PxQuat*)&v;
}
inline physx::PxQuat& operator~(Egg::Math::Float4& v)
{
	return *(physx::PxQuat*)&v;
}

inline const Egg::Math::Float3& operator~(const physx::PxVec3& v)
{
	return *(const Egg::Math::Float3*)&v;
}
inline Egg::Math::Float3& operator~(physx::PxVec3& v)
{
	return *(Egg::Math::Float3*)&v;
}

inline const Egg::Math::Float4& operator~(const physx::PxQuat& v)
{
	return *(const Egg::Math::Float4*)&v;
}
inline Egg::Math::Float4& operator~(physx::PxQuat& v)
{
	return *(Egg::Math::Float4*)&v;
}

using namespace physx;
static void toRadiansAndUnitAxis(PxQuat& q, PxReal& angle, PxVec3& axis)
{
	const PxReal quatEpsilon = (PxReal(1.0e-8f));
	const PxReal s2 = q.x * q.x + q.y * q.y + q.z * q.z;
	if (s2 < quatEpsilon * quatEpsilon)  // can't extract a sensible axis
	{
		angle = 0;
		axis = PxVec3(1, 0, 0);
	}
	else
	{
		const PxReal s = PxRecipSqrt(s2);
		axis = PxVec3(q.x, q.y, q.z) * s;
		angle = abs(q.w) < quatEpsilon ? PxPi : PxAtan2(s2 * s, q.w) * 2;
	}
}