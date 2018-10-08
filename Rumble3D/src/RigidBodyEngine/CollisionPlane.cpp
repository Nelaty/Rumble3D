#include "R3D/RigidBodyEngine/CollisionPlane.h"

namespace r3
{
	CollisionPlane::CollisionPlane(const glm::vec3& normal, 
								   const real offset,
								   const glm::vec2& halfSizes,
	                               const bool isHalfSpace)
		: CollisionPrimitive(R3D_PRIMITIVE_PLANE),
		m_normal(normal), 
		m_offset(offset),
		m_halfSizes(halfSizes),
		m_isHalfSpace(isHalfSpace)
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

	bool CollisionPlane::isHalfSpace() const
	{
		return m_isHalfSpace;
	}

	const glm::vec2& CollisionPlane::getHalfSizes() const
	{
		return m_halfSizes;
	}
}
