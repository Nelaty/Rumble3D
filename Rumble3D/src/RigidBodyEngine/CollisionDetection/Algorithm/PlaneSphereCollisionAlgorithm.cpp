#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlaneSphereCollisionAlgorithm.h"

namespace r3
{
	PlaneSphereCollisionAlgorithm::PlaneSphereCollisionAlgorithm()
	= default;

	PlaneSphereCollisionAlgorithm::~PlaneSphereCollisionAlgorithm()
	= default;

	bool PlaneSphereCollisionAlgorithm::generateContactDataImpl(RigidBody* rbPlane,
																CollisionPlane* plane,
																RigidBody* rbSphere,
																CollisionSphere* sphere,
																CollisionData& collisionData)
	{
		/// \todo: implement
		return false;
	}
}
