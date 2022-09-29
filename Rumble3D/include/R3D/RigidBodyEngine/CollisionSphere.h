#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	/**
	 * \brief CollisionPrimitive, which represents a sphere.
	 */
	class R3D_EXPORT CollisionSphere : public CollisionPrimitive
	{
	public:
		/**
		 * \brief CollisionSphere constructor.
		 * \param body The rigid body this collision sphere represents.
		 * \param radius The radius of the collision sphere.
		 * \param offset Offset from the represented rigid body.
		 */
		CollisionSphere(RigidBody* body,
						real radius, 
						const glm::mat4& offset = glm::mat4(1));
		~CollisionSphere() = default;

		/**
		 * \brief Get the radius of the collision sphere.
		 * \return The radius of the sphere.
		 */
		real getRadius() const;

	protected:
	
		real m_radius;
	};
}
