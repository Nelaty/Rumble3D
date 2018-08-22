#pragma once
#include "CollisionPrimitive.h"

#include <glm/glm.hpp>

#include <array>

namespace rum
{
	class RigidBody;

	class CollisionBox : public CollisionPrimitive
	{
	public:
		CollisionBox(RigidBody* body, const glm::mat4& offset, const glm::vec3& halfSize);
		~CollisionBox();

		glm::vec3 getHalfSize() const;

	protected:
		glm::vec3 m_halfSize; // Halbe Entfernung der Seiten vom Mittelpunkt eines Quaders

	private:
		void initVertices();

		std::array<glm::vec3, 8> m_vertices;
	};

}