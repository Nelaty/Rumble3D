#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"
#include "R3D/Common/Precision.h"
#include <glm/glm.hpp>

namespace r3
{
	// Die Klasse ist nicht abgeleitet von CollisionPrimitive,
	// da sie Wände und Böden darstellt, also nicht bewegliche 
	// Objekte.
	class R3D_DECLSPEC CollisionPlane : public CollisionPrimitive
	{
	public:
		CollisionPlane(const glm::vec3& normal,
					   real offset,
					   const glm::vec2& halfSizes = glm::vec2(1.0f, 1.0f),
					   bool isHalfSpace = false);
		~CollisionPlane();
		
		real getOffset() const;
		glm::vec3 getNormal() const;
		void setOffset(real offset);
		void setNormal(const glm::vec3 & normal);

		/** 
		 * Check if this plane defines a half space. 
		 * If this is the case, the normal will point away from this 
		 * half space.
		 */
		bool isHalfSpace() const;

		/** Get scaling in x-z directions */
		const glm::vec2& getHalfSizes() const;

	protected:
		glm::vec3 m_normal;
		real m_offset;
		glm::vec2 m_halfSizes;
		bool m_isHalfSpace;
	};
}