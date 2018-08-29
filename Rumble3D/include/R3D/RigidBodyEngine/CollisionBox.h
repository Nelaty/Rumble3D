#pragma once
#include "CollisionPrimitive.h"
#include "R3D/Common/Common.h"

#include <glm/glm.hpp>

#include <array>

namespace rum
{
	class RigidBody;

	class R3D_DECLSPEC CollisionBox : public CollisionPrimitive
	{
	public:
		explicit CollisionBox(RigidBody* body,
							  const glm::mat4& offset, 
							  const glm::vec3& halfSize);
		~CollisionBox();

		glm::vec3 getHalfSize() const;

		void generateContact(INarrowPhaseFilter* filter, CollisionPrimitive* other) override;

	protected:
		glm::vec3 m_halfSize; // Halbe Entfernung der Seiten vom Mittelpunkt eines Quaders

	private:
		void initVertices();

		std::array<glm::vec3, 8> m_vertices;
	};

}