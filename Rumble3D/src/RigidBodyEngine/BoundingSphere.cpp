#include "R3D/RigidBodyEngine/BoundingSphere.h"

#include <corecrt_math_defines.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>

namespace r3
{
	BoundingSphere::BoundingSphere()
	= default;

	BoundingSphere::BoundingSphere(const glm::vec3 & center, real radius)
		: m_center(center), 
		m_radius(radius)
	{
	}
	
	BoundingSphere::BoundingSphere(const BoundingSphere & one, const BoundingSphere & two)
	{
		const auto centerOffset = two.m_center - one.m_center;
		auto distance = glm::length2(centerOffset);
		const auto radiusDifference = two.m_radius - one.m_radius;
	
		// Liegen die Kugeln ineinander?
		if ((radiusDifference * radiusDifference) >= distance)
		{
			if (one.m_radius > two.m_radius) 
			{
				m_center = one.m_center;
				m_radius = one.m_radius;
			}
			else 
			{
				m_center = two.m_center;
				m_radius = two.m_radius;
			}
		}
		
		// Kugeln liegen nicht ineinander:
		else
		{
			distance = sqrt(distance);
			m_radius = (distance + one.m_radius + two.m_radius) * static_cast<real>(0.5);
	
			m_center = one.m_center;
			if (distance > 0)
			{
				m_center += centerOffset * ((m_radius - one.m_radius) / distance);
			}
		}
	}
	
	BoundingSphere::~BoundingSphere()
	= default;

	bool BoundingSphere::overlaps(const BoundingSphere* other) const
	{
		const auto distanceSquared = glm::length2(m_center - other->m_center);
		return distanceSquared < ((m_radius + other->m_radius) * (m_radius + other->m_radius));
	}
	
	real BoundingSphere::getVolume() const
	{
		return static_cast<real>(1.333333) * M_PI * m_radius * m_radius * m_radius;
	}
	
	real BoundingSphere::getGrowth(const BoundingSphere& other) const
	{
		const BoundingSphere newSphere(*this, other);
		return newSphere.m_radius*newSphere.m_radius - m_radius*m_radius;
	}
}