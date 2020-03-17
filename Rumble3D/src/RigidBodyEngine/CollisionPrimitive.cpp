#include "R3D/RigidBodyEngine/CollisionPrimitive.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include <glm/gtc/matrix_transform.inl>

#include <cassert>

namespace r3
{
	CollisionPrimitive::~CollisionPrimitive()
		= default;

	void CollisionPrimitive::calculateInternals()
	{
		const auto& transform = m_body->getTransform();
		glm::mat4 mat = transform.getRotationMat();
		mat[3] = glm::vec4(transform.getPosition(), 1.0f);

		m_transform = mat * m_offset;
	}

	glm::vec3 CollisionPrimitive::getAxis(const unsigned index) const
	{
		assert(index >= 0 && index <= 3);
		return m_transform[index];
	}

	const glm::mat4& CollisionPrimitive::getTransform() const
	{
		return m_transform;
	}

	RigidBody* CollisionPrimitive::getBody() const
	{
		return m_body;
	}

	CollisionPrimitiveType CollisionPrimitive::getType() const
	{
		return m_type;
	}

	CollisionPrimitive::CollisionPrimitive(const CollisionPrimitiveType type)
		: m_type(type)
	{
	}
}
