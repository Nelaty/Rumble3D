#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class R3D_DECLSPEC CollisionResolver
	{
	public:
		explicit CollisionResolver();
		virtual ~CollisionResolver();

		virtual void resolveCollisions(const CollisionData& collisionData) = 0;

	protected:
		
	};
}