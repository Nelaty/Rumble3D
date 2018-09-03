#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollision.h"

#include <vector>


namespace r3
{
	struct BroadPhaseCollision;

	class CollisionBox;
	class CollisionSphere;

	class R3D_DECLSPEC INarrowPhaseFilter
	{
	public:
		virtual ~INarrowPhaseFilter();

		virtual const CollisionData& generateCollisionData(
			const std::vector<BroadPhaseCollision>& collisions) = 0;

		virtual void generateCollisionData(CollisionBox* first, CollisionBox* second) = 0;
		virtual void generateCollisionData(CollisionBox* first, CollisionSphere* second) = 0;
		virtual void generateCollisionData(CollisionSphere* first, CollisionBox* second);
		virtual void generateCollisionData(CollisionSphere* first, CollisionSphere* second) = 0;

	protected:
		explicit INarrowPhaseFilter();

		
	};
}
