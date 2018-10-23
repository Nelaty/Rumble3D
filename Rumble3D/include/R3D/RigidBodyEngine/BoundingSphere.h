#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	/**
	 * \brief A bounding sphere is a kind of bounding volume.
	 */
	class R3D_DECLSPEC BoundingSphere
	{	
	public:
		BoundingSphere();
		/**
		 * \brief BoundingBox constructor
		 * \param center The center of the spehere in world coordinates.
		 * \param radius The radius of the sphere
		 */
		BoundingSphere(const glm::vec3& center, real radius);
		/** Create a bounding sphere which contains both given spheres. */
		/**
		 * \brief BoundingSphere constructor.
		 * \param one The first child bounding sphere.
		 * \param two The second child bounding sphere.
		 */
		BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);
		~BoundingSphere();

		/** 
		 * \brief Check if this bounding sphere overlaps with the
		 * given bounding sphere 
		 * \return True if they overlap, false otherwise.
		 */
		bool overlaps(const BoundingSphere* other) const;
		/** 
		 * \biref Get the volume of this bounding sphere. 
		 * \return The volume.
		 */
		real getVolume() const;
		/**
		 * \brief Get an approximation of how much a new bounding 
		 * sphere, including the given and this one, would be
		 * relatively to this one.
		 * \param other The added volume.
		 * \return The growth.
		 */
		real getGrowth(const BoundingSphere& other) const;
		
	protected:
		/**
		 * \brief Calculate the square of this spheres radius.
		 * \return The squared radius.
		 */
		real squaredRadius() const;

		glm::vec3 m_center;
		real m_radius{};
	};
}

