#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class R3D_DECLSPEC ICollisionResolutionFilter
	{
	public:
		virtual ~ICollisionResolutionFilter();

		virtual void resolve(const CollisionData& collisionData) = 0;

	protected:
		explicit ICollisionResolutionFilter();
	};
}