#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace rum
{
	CollisionSphere::CollisionSphere(RigidBody* body, glm::mat4 offset, real radius) 
		: m_radius{radius}
	{
		m_body = body;
		m_offset = offset;
	}
	
	CollisionSphere::~CollisionSphere()
	{
	}

	real CollisionSphere::GetRadius() const
	{
		return m_radius;
	}
}