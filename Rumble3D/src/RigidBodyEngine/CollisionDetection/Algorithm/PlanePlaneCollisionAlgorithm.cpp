#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlanePlaneCollisionAlgorithm.h"

namespace r3
{
	bool PlanePlaneCollisionAlgorithm::generateContactDataImpl(RigidBody* rbPlane1,
															   CollisionPlane* plane1,
															   RigidBody* rbPlane2,
															   CollisionPlane* plane2,
                                                               FixedSizeContainer<Contact>& collisionData)
	{
		/// \todo: implement
		return false;
	}
}
