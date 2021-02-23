#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IPlaneBoxCollisionAlgorithm.h"

namespace r3
{
	bool IPlaneBoxCollisionAlgorithm::generateContactData(RigidBody* first,
														  RigidBody* second,
														  CollisionData& collisionData)
	{
		const auto needSwap = first->getCollisionPrimitive()->getType() == R3D_PRIMITIVE_BOX;

		auto* rbPlane = needSwap ? second : first;
		auto* rbBox = needSwap ? first : second;

		auto* plane = static_cast<CollisionPlane*>(rbPlane->getCollisionPrimitive());
		auto* box = static_cast<CollisionBox*>(rbBox->getCollisionPrimitive());

		return generateContactDataImpl(rbPlane, plane,
									   rbBox, box,
									   collisionData);
	}
}
