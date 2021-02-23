#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/ISphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	bool ISphereSphereNarrowAlgorithm::generateContactData(RigidBody* first, RigidBody* second,
                                                           FixedSizeContainer<Contact>& collisionData)
	{
		const auto sphere1 = static_cast<CollisionSphere*>(first->getCollisionPrimitive());
		const auto sphere2 = static_cast<CollisionSphere*>(second->getCollisionPrimitive());

		return generateContactDataImpl(first, sphere1,
									   second, sphere2,
									   collisionData);
	}
}
