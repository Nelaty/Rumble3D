#pragma once
#include "CollisionPrimitive.h"
#include "R3D/Common/Common.h"

#include <glm/glm.hpp>

#include <array>

namespace r3
{
	class RigidBody;

	/**
	 * \brief CollisionPrimitive that represents a box.
	 */
	class R3D_DECLSPEC CollisionBox : public CollisionPrimitive
	{
	public:
		/**
		 * \brief CollisionBox constructor.
		 * \param body The rigid body represented by this primitive.
		 * \param halfSizes The half sizes of the box.
		 * \param offset The offset from the rigid body.
		 */
		explicit CollisionBox(RigidBody* body, 
							  const glm::vec3& halfSizes,
							  const glm::mat4& offset = glm::mat4(1));
		~CollisionBox();

		/**
		 * \brief Get the half sizes of the box.
		 * \return The half sizes.
		 */
		const glm::vec3& getHalfSize() const;

	private:
		glm::vec3 m_halfSizes;

		/**
		 * \brief Calculate vertices of this box once and store them.
		 * \details Vertices depend on the half sizes of the box.
		 */
		void initVertices();

		std::array<glm::vec3, 8> m_vertices;
	};

}