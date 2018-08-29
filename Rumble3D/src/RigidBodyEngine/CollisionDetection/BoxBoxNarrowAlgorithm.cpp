#include "R3D/RigidBodyEngine/CollisionDetection/BoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"

namespace rum
{
	BoxBoxNarrowAlgorithm::BoxBoxNarrowAlgorithm()
	= default;

	BoxBoxNarrowAlgorithm::~BoxBoxNarrowAlgorithm()
	= default;

	bool BoxBoxNarrowAlgorithm::generateContactData(CollisionBox* first,
													CollisionBox* second,
													CollisionData& collisionData)
	{
		/// \todo implement
		return false;
	}
}
