#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace rum
{
	class ICollisionResolver
	{
	public:
		virtual ~ICollisionResolver();

		virtual void resolveCollisions(const CollisionData& collisionData) = 0;

	protected:
		explicit ICollisionResolver();
	};
}