#pragma once
#include "CollisionPrimitive.h"

#include <glm/glm.hpp>

namespace rum
{
	class RigidBody;

	class CollisionBox : public CollisionPrimitive
	{
	public:
		CollisionBox(RigidBody * m_body, glm::mat4 offset, glm::vec3 _halfsize);
		~CollisionBox();

		glm::vec3 getHalfSize() const;

	protected:
		glm::vec3 m_halfSize; // Halbe Entfernung der Seiten vom Mittelpunkt eines Quaders

	private:
		void initVertices();

		glm::vec3 m_vertices[8];
	};

}