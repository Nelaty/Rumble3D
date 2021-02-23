#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IPlanePlaneCollisionAlgorithm.h"

namespace r3
{
	bool IPlanePlaneCollisionAlgorithm::generateContactData(RigidBody* first,
															RigidBody* second,
                                                            FixedSizeContainer<Contact>& collisionData)
	{
		auto* plane1 = static_cast<CollisionPlane*>(first->getCollisionPrimitive());
		auto* plane2 = static_cast<CollisionPlane*>(second->getCollisionPrimitive());

		return generateContactDataImpl(first, plane1,
									   second, plane2,
									   collisionData);
	}
}
