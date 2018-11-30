#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/NullAlgorithm.h"

namespace r3
{
	NullAlgorithm::NullAlgorithm()
	= default;

	NullAlgorithm::~NullAlgorithm()
	= default;

	bool NullAlgorithm::generateContactData(RigidBody* first, 
											RigidBody* second,
											CollisionData& collisionData)
	{
		return false;
	}
}
