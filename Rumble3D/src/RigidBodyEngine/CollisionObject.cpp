#include "R3D/RigidBodyEngine/CollisionObject.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

namespace r3
{
	void CollisionObject::setCollisionPrimitive(CollisionPrimitive* collisionPrimitive)
	{
		m_collisionPrimitive = collisionPrimitive;
	}

	CollisionPrimitive* CollisionObject::getCollisionPrimitive() const
	{
		return m_collisionPrimitive;
	}

	CollisionObject::CollisionObject(CollisionPrimitive* collisionPrimitive)
		: m_collisionPrimitive{collisionPrimitive}
	{
	}

	const Transform3D& CollisionObject::getTransform() const
	{
		return m_transform;
	}

	Transform3D& CollisionObject::getTransform()
	{
		return m_transform;
	}
}
