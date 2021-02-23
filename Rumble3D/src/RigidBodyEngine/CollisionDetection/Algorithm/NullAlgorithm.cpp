#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/NullAlgorithm.h"

namespace r3
{
	bool NullAlgorithm::generateContactData(RigidBody* first, 
											RigidBody* second,
                                            FixedSizeContainer<Contact>& collisionData)
	{
		return false;
	}
}
