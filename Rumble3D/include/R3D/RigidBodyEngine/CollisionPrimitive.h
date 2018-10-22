#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPrimitiveType.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	class CollisionBox;
	class CollisionSphere;

	/**
	 * \brief Abstract collision shape, which can collide with
	 * other collision primitives.
	 */
	class R3D_DECLSPEC CollisionPrimitive
	{
	public:
		virtual ~CollisionPrimitive();	

		/**
		 * \brief Calculates its transformation.
		 */
		void calculateInternals();
		/**
		 * \brief Get an axis from the transformation matrix.
		 * \param index The index of the axis.
		 * \return The axis;
		 */
		glm::vec3 getAxis(unsigned index) const;
		/**
		 * \brief Get the transform of this primitive.
		 * \return The transform.
		 */
		const glm::mat4& getTransform() const;

		/**
		 * \brief Get the rigid body, which uses this collision
		 * primitive.
		 * \return The rigid body.
		 */
		RigidBody* getBody() const;

		/**
		 * \brief Get the type of this primitive.
		 * \return The primitive specific type.
		 */
		CollisionPrimitiveType getType() const;

	protected:
		/**
		 * \brief CollisionPrimitive constructor.
		 * \param type The type of the primitive.
		 */
		explicit CollisionPrimitive(CollisionPrimitiveType type);

		/**
		 * \brief The rigid body this collision primitive represents.
		 */
		RigidBody* m_body{};

		/**
		 * \brief Offset from the represented rigid body.
		 */
		glm::mat4 m_offset;

		glm::mat4 m_transform;

	private:
		CollisionPrimitiveType m_type;
	};
}