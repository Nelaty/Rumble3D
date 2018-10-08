#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/ISphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	ISphereSphereNarrowAlgorithm::~ISphereSphereNarrowAlgorithm()
	= default;

	bool ISphereSphereNarrowAlgorithm::generateContactData(RigidBody* first, RigidBody* second,
		CollisionData& collisionData)
	{
		const auto sphere1 = static_cast<CollisionSphere*>(first->getCollisionPrimitive());
		const auto sphere2 = static_cast<CollisionSphere*>(second->getCollisionPrimitive());

		return generateContactDataImpl(first, sphere1,
									   second, sphere2,
									   collisionData);
	}

	ISphereSphereNarrowAlgorithm::ISphereSphereNarrowAlgorithm()
	= default;
}
