#include "R3D/RigidBodyEngine/CollisionPlane.h"

namespace rum
{
	CollisionPlane::CollisionPlane(const glm::vec3& normal, const real offset) 
		: m_normal(normal), 
		m_offset(offset)
	{
	}
	
	CollisionPlane::~CollisionPlane()
	{
	}

	real CollisionPlane::GetOffset() const
	{
		return m_offset;
	}
	
	glm::vec3 CollisionPlane::GetNormal() const
	{
		return m_normal;
	}
	
	void CollisionPlane::SetOffset(const real offset)
	{
		m_offset = offset;
	}
	
	void CollisionPlane::SetNormal(const glm::vec3 & normal)
	{
		m_normal = normal;
	}
}
