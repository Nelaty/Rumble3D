#include "R3D/RigidBodyEngine/CollisionDetection/SphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace rum
{
	SphereSphereNarrowAlgorithm::SphereSphereNarrowAlgorithm()
	= default;

	SphereSphereNarrowAlgorithm::~SphereSphereNarrowAlgorithm()
	= default;

	bool SphereSphereNarrowAlgorithm::generateContactData(CollisionSphere* first,
														  CollisionSphere* second,
														  CollisionData& collisionData)
	{
		/// \todo implement
		return false;
	}
}
