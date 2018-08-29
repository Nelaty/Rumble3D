#include "R3D/RigidBodyEngine/CollisionObject.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

namespace rum
{
	CollisionObject::~CollisionObject()
	= default;

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
}
