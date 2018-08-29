#include "R3D/RigidBodyEngine/CollisionDetection/BoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace rum
{
	BoxSphereNarrowAlgorithm::BoxSphereNarrowAlgorithm()
	= default;

	BoxSphereNarrowAlgorithm::~BoxSphereNarrowAlgorithm()
	= default;

	bool BoxSphereNarrowAlgorithm::generateContactData(CollisionBox* first,
													   CollisionSphere* second,
													   CollisionData& collisionData)
	{
		/// \todo implement
		return false;
	}
}
