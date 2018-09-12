#include "R3D/RigidBodyEngine/CollisionDetection/IBoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	IBoxSphereNarrowAlgorithm::~IBoxSphereNarrowAlgorithm()
	= default;

	bool IBoxSphereNarrowAlgorithm::generateContactData(CollisionPrimitive* first, 
														CollisionPrimitive* second,
														CollisionData& collisionData)
	{
		return generateContactData(static_cast<CollisionBox*>(first),
								   static_cast<CollisionSphere*>(second),
								   collisionData);
	}

	bool IBoxSphereNarrowAlgorithm::generateContactData(CollisionSphere* first,
														CollisionBox* second,
														CollisionData& collisionData)
	{
		return generateContactData(second, first, collisionData);
	}

	IBoxSphereNarrowAlgorithm::IBoxSphereNarrowAlgorithm()
	= default;
}
