#include "R3D/RigidBodyEngine/CollisionDetection/SphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	SphereSphereNarrowAlgorithm::SphereSphereNarrowAlgorithm()
	= default;

	SphereSphereNarrowAlgorithm::~SphereSphereNarrowAlgorithm()
	= default;

	bool SphereSphereNarrowAlgorithm::generateContactDataImpl(RigidBody* rbSphere1, CollisionSphere* sphere1,
															  RigidBody* rbSphere2, CollisionSphere* sphere2,
															  CollisionData& collisionData)
	{
		/// \todo implement
		return false;
	}
}
