#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

#include <glm/glm.hpp>

namespace r3
{
	/**
	 * \brief CollisionPrimitive that represents a plane.
	 */
	class R3D_DECLSPEC CollisionPlane : public CollisionPrimitive
	{
	public:
		/**
		 * \brief CollisionPlane constructor
		 * \param normal Defines the front side of the plane.
		 * \param offset The offset along the normal.
		 * \param halfSizes Size of the plane.
		 * \param isHalfSpace Flag to also use a plane as a half space.
		 */
		CollisionPlane(const glm::vec3& normal,
					   real offset,
					   const glm::vec2& halfSizes = glm::vec2(1.0f, 1.0f),
					   bool isHalfSpace = false);
		~CollisionPlane() = default;

		/**
		 * \brief Set the current offset.
		 * \param offset The offset along the normal.
		 */
		void setOffset(real offset);
		/**
		 * \brief Get the current offset.
		 * \return The offset along the normal
		 */
		real getOffset() const;

		/**
		 * \brief Set the current normal.
		 * \param normal The new normal.
		 */
		void setNormal(const glm::vec3 & normal);
		/**
		 * \brief Get the current normal.
		 * \return The normal.
		 */
		glm::vec3 getNormal() const;

		/** 
		 * \brief Check if this plane defines a half space. 
		 * \return True if it is a half space, false otherwise.
		 */
		bool isHalfSpace() const;

		/** 
		 * \brief Get the size of the plane.
		 * \return The half sizes.
		 */
		const glm::vec2& getHalfSizes() const;

	protected:
		glm::vec3 m_normal;
		real m_offset;
		glm::vec2 m_halfSizes;
		bool m_isHalfSpace;
	};
}