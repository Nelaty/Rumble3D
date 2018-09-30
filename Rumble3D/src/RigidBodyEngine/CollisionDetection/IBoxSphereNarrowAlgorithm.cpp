#include "R3D/RigidBodyEngine/CollisionDetection/IBoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	IBoxSphereNarrowAlgorithm::~IBoxSphereNarrowAlgorithm()
	= default;

	bool IBoxSphereNarrowAlgorithm::generateContactData(RigidBody* first,
														RigidBody* second,
														CollisionData& collisionData)
	{
		// Check if the first collision primitive is a sphere
		const bool needSwap = first->getCollisionPrimitive()->getType() == R3D_PRIMITIVE_SPHERE;

		RigidBody* rbBox = needSwap ? second : first;
		RigidBody* rbSphere = needSwap ? first : second;

		const auto box = static_cast<CollisionBox*>(rbBox->getCollisionPrimitive());
		const auto sphere = static_cast<CollisionSphere*>(rbSphere->getCollisionPrimitive());

		return generateContactDataImpl(rbBox, box,
									   rbSphere, sphere,
									   collisionData);
	}

	IBoxSphereNarrowAlgorithm::IBoxSphereNarrowAlgorithm()
	= default;
}
