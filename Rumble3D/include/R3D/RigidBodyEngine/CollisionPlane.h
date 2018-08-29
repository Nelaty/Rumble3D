#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include <glm/glm.hpp>

namespace rum
{
	// Die Klasse ist nicht abgeleitet von CollisionPrimitive,
	// da sie Wände und Böden darstellt, also nicht bewegliche 
	// Objekte.
	class R3D_DECLSPEC CollisionPlane
	{
	public:
		CollisionPlane(const glm::vec3 & normal, real offset);
		~CollisionPlane();
		
		real getOffset() const;
		glm::vec3 getNormal() const;
		void setOffset(real offset);
		void setNormal(const glm::vec3 & normal);

	protected:
		glm::vec3 m_normal;
		real m_offset;
	};
}