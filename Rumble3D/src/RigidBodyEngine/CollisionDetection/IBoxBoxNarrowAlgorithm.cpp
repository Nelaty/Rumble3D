#include "R3D/RigidBodyEngine/CollisionDetection/IBoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"

namespace r3
{
	IBoxBoxNarrowAlgorithm::~IBoxBoxNarrowAlgorithm()
	= default;

	bool IBoxBoxNarrowAlgorithm::generateContactData(CollisionPrimitive* first,
													 CollisionPrimitive* second,
													 CollisionData& collisionData)
	{
		return generateContactData(static_cast<CollisionBox*>(first),
								   static_cast<CollisionBox*>(second),
								   collisionData);
	}

	IBoxBoxNarrowAlgorithm::IBoxBoxNarrowAlgorithm()
	= default;
}
