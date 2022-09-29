#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class R3D_EXPORT BoundingBox
	{
	public:
	
		BoundingBox();
		/**
		 * \brief BoundingBox constructor.
		 * \param center The center of the box in world coordinates.
		 * \param bounds Half sizes of the box.
		 */
		BoundingBox(const glm::vec3& center, const glm::vec3& halfSizes);
		/**
		 * \brief BoundingBox constructor. Create a bounding box
		 * which contains both given boxes.
		 * \param one The first contained bounding box.
		 * \param two The second contained bounding box.
		 */
		BoundingBox(const BoundingBox& one, const BoundingBox& two);
		~BoundingBox() = default;
		
		/**
		 * \brief Check the given bounding box overlaps with this one.
		 * \param other The other bounding box to check against.
		 * \return True if there is a collision, false otherwise.
		 */
		bool overlaps(const BoundingBox* other) const;
		/** 
		 * \brief Get the volume of this bounding box. 
		 * \return The volume.
		 */
		real getVolume() const;
		/**
		 * \brief Get an approximation of how much a new bounding
		 * box, including the given and this one, would be
		 * relatively to this one.
		 * \param other The added volume.
		 * \return The growth.
		 */
		real getGrowth(const BoundingBox& other) const;

	protected:
		glm::vec3 m_center;
		glm::vec3 m_halfSizes;
	};
}

