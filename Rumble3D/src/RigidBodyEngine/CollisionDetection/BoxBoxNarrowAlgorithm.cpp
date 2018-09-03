#include "R3D/RigidBodyEngine/CollisionDetection/BoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"

namespace r3
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
