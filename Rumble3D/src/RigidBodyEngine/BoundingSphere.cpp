#include "R3D/RigidBodyEngine/BoundingSphere.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>

namespace rum
{
	BoundingSphere::BoundingSphere()
	{
	}
	
	BoundingSphere::BoundingSphere(const glm::vec3 & center, real radius)
		: m_center(center), 
		m_radius(radius)
	{
	}
	
	BoundingSphere::BoundingSphere(const BoundingSphere & one, const BoundingSphere & two)
	{
		glm::vec3 centerOffset = two.m_center - one.m_center;
		real distance = glm::length2(centerOffset);
		real radiusDifference = two.m_radius - one.m_radius;
	
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
	{
	}

	bool BoundingSphere::Overlaps(const BoundingSphere* other) const
	{
		real distanceSquared = glm::length2(m_center - other->m_center);
		return distanceSquared < ((m_radius + other->m_radius) * (m_radius + other->m_radius));
	}
	
	real BoundingSphere::GetSize() const
	{
		return static_cast<real>(1.333333) * M_PI * m_radius * m_radius * m_radius;
	}
	
	real BoundingSphere::GetGrowth(const BoundingSphere& other) const
	{
		BoundingSphere newSphere(*this, other);
		return newSphere.m_radius*newSphere.m_radius - m_radius*m_radius;
	}
}

#ifdef _USE_MATH_DEFINES
#undef _USE_MATH_DEFINES
#endif // _USE_MATH_DEFINES