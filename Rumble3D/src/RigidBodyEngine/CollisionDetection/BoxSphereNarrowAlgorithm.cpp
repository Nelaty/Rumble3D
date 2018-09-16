#include "R3D/RigidBodyEngine/CollisionDetection/BoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	BoxSphereNarrowAlgorithm::BoxSphereNarrowAlgorithm()
	= default;

	BoxSphereNarrowAlgorithm::~BoxSphereNarrowAlgorithm()
	= default;

	bool BoxSphereNarrowAlgorithm::generateContactDataImpl(RigidBody* rbBox, CollisionBox* box,
														   RigidBody* rbSphere, CollisionSphere* sphere, 
														   CollisionData& collisionData)
	{
		/// \todo implement
		return false;
	}
}
