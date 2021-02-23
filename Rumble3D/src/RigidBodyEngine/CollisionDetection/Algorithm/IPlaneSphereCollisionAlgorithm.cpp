#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IPlaneSphereCollisionAlgorithm.h"

namespace r3
{
	bool IPlaneSphereCollisionAlgorithm::generateContactData(RigidBody* first,
															 RigidBody* second,
															 CollisionData& collisionData)
	{
		const auto needSwap = first->getCollisionPrimitive()->getType() == R3D_PRIMITIVE_SPHERE;

		auto* rbPlane = needSwap ? second : first;
		auto* rbSphere = needSwap ? first : second;

		auto* plane = static_cast<CollisionPlane*>(rbPlane->getCollisionPrimitive());
		auto* sphere = static_cast<CollisionSphere*>(rbSphere->getCollisionPrimitive());

		return generateContactDataImpl(rbPlane, plane,
									   rbSphere, sphere,
									   collisionData);
	}
}
