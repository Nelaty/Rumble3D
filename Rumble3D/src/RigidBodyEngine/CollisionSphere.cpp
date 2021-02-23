#include "R3D/RigidBodyEngine/CollisionSphere.h"
#include "R3D/Utility/InertiaTensorGenerator.h"

namespace r3
{
	CollisionSphere::CollisionSphere(RigidBody* body, const real radius, const glm::mat4& offset)
		: CollisionPrimitive(R3D_PRIMITIVE_SPHERE),
		m_radius{radius}
	{
		m_body = body;
		m_offset = offset;
	}

	real CollisionSphere::getRadius() const
	{
		return m_radius;
	}
}
