#pragma once
#include "R3D/Common/Precision.h"
#include <glm/glm.hpp>

namespace rum
{
	// Die Klasse ist nicht abgeleitet von CollisionPrimitive,
	// da sie Wände und Böden darstellt, also nicht bewegliche 
	// Objekte.
	class CollisionPlane
	{
	public:
		CollisionPlane(const glm::vec3 & normal, const real offset);
		~CollisionPlane();
		
		real GetOffset() const;
		glm::vec3 GetNormal() const;
		void SetOffset(const real offset);
		void SetNormal(const glm::vec3 & normal);

	protected:
		glm::vec3 m_normal;
		real m_offset;
	};
}