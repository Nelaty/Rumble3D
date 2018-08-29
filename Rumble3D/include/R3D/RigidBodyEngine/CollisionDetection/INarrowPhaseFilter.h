#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollision.h"

#include <vector>


namespace rum
{
	struct BroadPhaseCollision;

	class CollisionBox;
	class CollisionSphere;

	class INarrowPhaseFilter
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
