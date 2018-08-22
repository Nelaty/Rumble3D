#pragma once
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class BoundingSphere
	{	
	public:
		BoundingSphere();
		BoundingSphere(const glm::vec3& center, real radius);
		/** Create a bounding sphere which contains both given spheres. */
		BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);
		~BoundingSphere();

		/** 
		 * Check if this bounding sphere overlaps with the given bounding sphere 
		 * \return True if they overlap, false otherwise.
		 */
		bool overlaps(const BoundingSphere* other) const;
		/** Get the volume of this bounding sphere. */
		real getVolume() const;
		/** 
		 * Gibt einen Wert zurück, der das Wachstum einer Kugel durch eine
		 * andere Kugel beschreibt, indem Näherungen der Oberflächen 
		 * berechnet werden.
		 */		 
		real getGrowth(const BoundingSphere& other) const;
		
	protected:
		glm::vec3 m_center;
		real m_radius{};
	};
}

