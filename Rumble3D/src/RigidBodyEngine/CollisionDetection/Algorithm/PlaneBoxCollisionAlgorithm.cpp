#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlaneBoxCollisionAlgorithm.h"

namespace r3
{
	PlaneBoxCollisionAlgorithm::PlaneBoxCollisionAlgorithm()
	= default;

	PlaneBoxCollisionAlgorithm::~PlaneBoxCollisionAlgorithm()
	= default;

	bool PlaneBoxCollisionAlgorithm::generateContactDataImpl(RigidBody* rbPlane, 
															 CollisionPlane* plane,
															 RigidBody* rbBox,
															 CollisionBox* box,
															 CollisionData& collisionData)
	{
		/// \todo: implement
		return false;
	}
}
