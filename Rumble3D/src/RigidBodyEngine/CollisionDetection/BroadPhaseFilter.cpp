#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseFilter.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	BroadPhaseFilter::BroadPhaseFilter()
	= default;

	BroadPhaseFilter::~BroadPhaseFilter()
	= default;

	void BroadPhaseFilter::generateCollisions(const std::vector<RigidBody*>& rigidBodies,
											  BroadPhaseCollisionData& data)
	{
		/// \todo use rigid body mask and layout
	}
}
