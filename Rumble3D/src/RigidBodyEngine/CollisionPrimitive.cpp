#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

namespace rum
{
	CollisionPrimitive::~CollisionPrimitive()
	{

	}

	void CollisionPrimitive::CalculateInternals()
	{
		m_transform = m_body->getTransformationMatrix() * m_offset;
	}

	glm::vec3 CollisionPrimitive::GetAxis(unsigned index) const
	{
		return m_transform[index];
	}

	const glm::mat4& CollisionPrimitive::GetTransform() const
	{
		return m_transform;
	}

	RigidBody* CollisionPrimitive::GetBody() const
	{
		return m_body;
	}

	CollisionPrimitive::CollisionPrimitive()
	{
	}
}