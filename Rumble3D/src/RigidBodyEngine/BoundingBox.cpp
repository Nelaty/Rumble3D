#include "R3D/RigidBodyEngine/BoundingBox.h"

#include <glm/gtx/norm.hpp>

namespace r3
{
	BoundingBox::BoundingBox()
		: m_center{0.5, 0.5, 0.5},
		m_bounds{1.0, 1.0, 1.0}
	{
	}

	BoundingBox::BoundingBox(const glm::vec3& center, const glm::vec3& bounds)
		: m_center{center},
		m_bounds{bounds}
	{
	}

	BoundingBox::BoundingBox(const BoundingBox& one, const BoundingBox& two)
	{
		const auto dist = one.m_center - two.m_center;
		const auto extends = (one.m_bounds + two.m_bounds) * static_cast<real>(0.5);

		m_bounds.x = dist.x + extends.x;
		m_bounds.y = dist.y + extends.y;
		m_bounds.z = dist.z + extends.z;
		
		m_center.x = m_bounds.x * static_cast<real>(0.5);
		m_center.y = m_bounds.y * static_cast<real>(0.5);
		m_center.z = m_bounds.z * static_cast<real>(0.5);
	}

	BoundingBox::~BoundingBox()
	{
	}

	bool BoundingBox::overlaps(const BoundingBox* other) const
	{
		// Check all six sides
		auto doesntCollide = false;
		// Front
		doesntCollide &= other->m_center.z + other->m_bounds.z * 0.5 <
			m_center.z - m_bounds.z * 0.5;
		
		// Behind
		doesntCollide &= doesntCollide ||
			other->m_center.z - other->m_bounds.z * 0.5 >
			m_center.z + m_bounds.z * 0.5;
	
		// Over
		doesntCollide &= doesntCollide || 
			other->m_center.y + other->m_bounds.y * 0.5 <
			m_center.y - m_bounds.y * 0.5;
	
		// Under
		doesntCollide &= doesntCollide || 
			other->m_center.y - other->m_bounds.y * 0.5 >
			m_center.y + m_bounds.y * 0.5;
	
		// Left
		doesntCollide &= doesntCollide || 
			other->m_center.x + other->m_bounds.x * 0.5 <
			m_center.x - m_bounds.x * 0.5;
	
		// Right
		doesntCollide &= doesntCollide || 
			other->m_center.x - other->m_bounds.x * 0.5 >
			m_center.x + m_bounds.x * 0.5;
		
		return !doesntCollide;
	}

	real BoundingBox::getVolume() const
	{
		return m_bounds.x * m_bounds.y * m_bounds.z;
	}

	real BoundingBox::getGrowth(const BoundingBox &other) const
	{
		const BoundingBox newBox(*this, other);
		return glm::length2(newBox.m_bounds) * glm::length2(newBox.m_bounds) -
			glm::length2(m_bounds) * glm::length2(m_bounds);
	}
}