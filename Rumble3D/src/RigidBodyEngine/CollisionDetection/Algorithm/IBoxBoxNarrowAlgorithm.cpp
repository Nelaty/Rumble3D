#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IBoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"

namespace r3
{
	bool IBoxBoxNarrowAlgorithm::generateContactData(RigidBody* first,
													 RigidBody* second,
                                                     FixedSizeContainer<Contact>& collisionData)
	{
		const auto box1 = static_cast<CollisionBox*>(first->getCollisionPrimitive());
		const auto box2 = static_cast<CollisionBox*>(second->getCollisionPrimitive());

		return generateContactDataImpl(first, box1,
									   second, box2,
									   collisionData);
	}
}
