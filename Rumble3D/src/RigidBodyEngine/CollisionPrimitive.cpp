#include "R3D/RigidBodyEngine/CollisionPrimitive.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseFilter.h"

namespace r3
{
	CollisionPrimitive::~CollisionPrimitive()
		= default;

	void CollisionPrimitive::calculateInternals()
	{
		m_transform = m_body->getTransformationMatrix() * m_offset;
	}

	glm::vec3 CollisionPrimitive::getAxis(unsigned index) const
	{
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
