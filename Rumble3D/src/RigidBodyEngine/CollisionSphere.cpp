#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace rum
{
	CollisionSphere::CollisionSphere(RigidBody* body, const glm::mat4& offset, const real radius) 
		: m_radius{radius}
	{
		m_body = body;
		m_offset = offset;
	}
	
	CollisionSphere::~CollisionSphere()
	= default;

	real CollisionSphere::getRadius() const
	{
		return m_radius;
	}
}