#pragma once
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(const glm::vec3& center, const glm::vec3& bounds);
		// Erstellt BoundingSphere, die die beiden Kugeln beinhaltet
		BoundingBox(const BoundingBox& one, const BoundingBox& two);
		~BoundingBox();

		// Gibt true zurück, wenn sich die BoundingSphere mit other überlappt
		// und sonst false
		bool Overlaps(const BoundingBox* other) const;
		real GetSize() const;
		// Gibt einen Wert zurück, der das Wachstum einer Kugel durch eine
		// andere Kugel beschreibt, indem Näherungen der Oberflächen 
		// berechnet werden.
		real GetGrowth(const BoundingBox& other) const;

	protected:
		glm::vec3 m_center;
		glm::vec3 m_bounds;
	};
}

