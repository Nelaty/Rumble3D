#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlanePlaneCollisionAlgorithm.h"

namespace r3
{
	PlanePlaneCollisionAlgorithm::PlanePlaneCollisionAlgorithm()
	= default;

	PlanePlaneCollisionAlgorithm::~PlanePlaneCollisionAlgorithm()
	= default;

	bool PlanePlaneCollisionAlgorithm::generateContactDataImpl(RigidBody* rbPlane1,
															   CollisionPlane* plane1,
															   RigidBody* rbPlane2,
															   CollisionPlane* plane2,
															   CollisionData& collisionData)
	{
		/// \todo: implement
		return false;
	}
}
