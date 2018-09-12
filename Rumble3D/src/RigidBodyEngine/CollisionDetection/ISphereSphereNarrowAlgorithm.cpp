#include "R3D/RigidBodyEngine/CollisionDetection/ISphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	ISphereSphereNarrowAlgorithm::~ISphereSphereNarrowAlgorithm()
	= default;

	bool ISphereSphereNarrowAlgorithm::generateContactData(CollisionPrimitive* first, CollisionPrimitive* second,
		CollisionData& collisionData)
	{
		return generateContactData(static_cast<CollisionSphere*>(first),
								   static_cast<CollisionSphere*>(second),
								   collisionData);
	}

	ISphereSphereNarrowAlgorithm::ISphereSphereNarrowAlgorithm()
	= default;
}
