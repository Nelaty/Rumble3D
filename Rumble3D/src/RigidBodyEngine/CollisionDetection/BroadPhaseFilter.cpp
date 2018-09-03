#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseFilter.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	BroadPhaseFilter::BroadPhaseFilter()
	= default;

	BroadPhaseFilter::~BroadPhaseFilter()
	= default;

	std::vector<BroadPhaseCollision> BroadPhaseFilter::generateCollisions(const std::vector<RigidBody*>& rigidBodies)
	{
		return std::vector<BroadPhaseCollision>();
	}
}
