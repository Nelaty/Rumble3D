#include "R3D/RigidBodyEngine/CollisionDetection/BoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"

namespace r3
{
	BoxBoxNarrowAlgorithm::BoxBoxNarrowAlgorithm()
	= default;

	BoxBoxNarrowAlgorithm::~BoxBoxNarrowAlgorithm()
	= default;

	bool BoxBoxNarrowAlgorithm::generateContactDataImpl(RigidBody* rbBox1, CollisionBox* box1, 
														RigidBody* rbBox2, CollisionBox* box2,
														CollisionData& collisionData)
	{
		/// \todo implement
		return false;
	}
}
