#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IPlanePlaneCollisionAlgorithm.h"

namespace r3
{
	IPlanePlaneCollisionAlgorithm::~IPlanePlaneCollisionAlgorithm()
	= default;

	bool IPlanePlaneCollisionAlgorithm::generateContactData(RigidBody* first,
															RigidBody* second,
															CollisionData& collisionData)
	{
		auto* plane1 = static_cast<CollisionPlane*>(first->getCollisionPrimitive());
		auto* plane2 = static_cast<CollisionPlane*>(second->getCollisionPrimitive());

		return generateContactDataImpl(first, plane1,
									   second, plane2,
									   collisionData);
	}

	IPlanePlaneCollisionAlgorithm::IPlanePlaneCollisionAlgorithm()
	= default;
}
