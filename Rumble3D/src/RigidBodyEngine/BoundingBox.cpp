#include "R3D/RigidBodyEngine/BoundingBox.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

namespace r3
{
	BoundingBox::BoundingBox()
		: m_center{real(0.5), real(0.5), real(0.5)},
		m_halfSizes{real(1), real(1), real(1) }
	{
	}

	BoundingBox::BoundingBox(const glm::vec3& center, const glm::vec3& halfSizes)
		: m_center{center},
		m_halfSizes{halfSizes}
	{
	}

	BoundingBox::BoundingBox(const BoundingBox& one, const BoundingBox& two)
	{
		const auto dist = one.m_center - two.m_center;
		const auto extends = one.m_halfSizes + two.m_halfSizes;

		m_halfSizes = real(0.5) * dist + extends;
		m_center = one.m_center + real(0.5) * dist;
	}

	bool BoundingBox::overlaps(const BoundingBox* other) const
	{
		// Check all six sides
		auto doesntCollide = false;
		// Front
		doesntCollide &= other->m_center.z + other->m_halfSizes.z <
			m_center.z - m_halfSizes.z;
		
		// Behind
		doesntCollide &= doesntCollide ||
			other->m_center.z - other->m_halfSizes.z >
			m_center.z + m_halfSizes.z;
	
		// Over
		doesntCollide &= doesntCollide || 
			other->m_center.y + other->m_halfSizes.y <
			m_center.y - m_halfSizes.y;
	
		// Under
		doesntCollide &= doesntCollide || 
			other->m_center.y - other->m_halfSizes.y >
			m_center.y + m_halfSizes.y;
	
		// Left
		doesntCollide &= doesntCollide || 
			other->m_center.x + other->m_halfSizes.x <
			m_center.x - m_halfSizes.x;
	
		// Right
		doesntCollide &= doesntCollide || 
			other->m_center.x - other->m_halfSizes.x >
			m_center.x + m_halfSizes.x;
		
		return !doesntCollide;
	}

	real BoundingBox::getVolume() const
	{
		return real(8) * m_halfSizes.x * m_halfSizes.y * m_halfSizes.z;
	}

	real BoundingBox::getGrowth(const BoundingBox &other) const
	{
		const BoundingBox newBox(*this, other);
		return glm::length2(newBox.m_halfSizes) * glm::length2(newBox.m_halfSizes) -
			glm::length2(m_halfSizes) * glm::length2(m_halfSizes);
	}
}