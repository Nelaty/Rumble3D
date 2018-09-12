#include "R3D/RigidBodyEngine/CollisionPlane.h"

namespace r3
{
	CollisionPlane::CollisionPlane(const glm::vec3& normal, const real offset) 
		: CollisionPrimitive(R3D_PRIMITIVE_PLANE),
		m_normal(normal), 
		m_offset(offset)
	{
	}
	
	CollisionPlane::~CollisionPlane()
	= default;

	real CollisionPlane::getOffset() const
	{
		return m_offset;
	}
	
	glm::vec3 CollisionPlane::getNormal() const
	{
		return m_normal;
	}
	
	void CollisionPlane::setOffset(const real offset)
	{
		m_offset = offset;
	}
	
	void CollisionPlane::setNormal(const glm::vec3 & normal)
	{
		m_normal = normal;
	}
}
