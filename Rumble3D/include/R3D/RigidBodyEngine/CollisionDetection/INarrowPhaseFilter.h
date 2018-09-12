#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollisionData.h"

namespace r3
{
	struct CollisionPair;

	class CollisionBox;
	class CollisionSphere;

	class R3D_DECLSPEC INarrowPhaseFilter
	{
	public:
		virtual ~INarrowPhaseFilter();

		virtual void generateCollisionData(const BroadPhaseCollisionData& broadPhaseData,
										   CollisionData& collisions) = 0;

	protected:
		explicit INarrowPhaseFilter();
	};
}
