#pragma once
#include "ForceGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	/**
	 * \brief An AnchoredSpring is a force generator that simulates
	 * spring forces.
	 * \details One end of the spring is a static point.
	 */
	class R3D_DECLSPEC AnchoredSpring : public ForceGenerator
	{
	public:
		/**
		 * \brief AnchoredSpring generator
		 * \param anchor The static end of the spring in world coordinates.
		 * \param localConnectionPoint Connection point of the rigid
		 * body (in local coordinates of said body).
		 * \param springConstant The hardness of the spring.
		 * \param restLength The distance at which no forces act.
		 */
		explicit AnchoredSpring(const glm::vec3& anchor,
								const glm::vec3& localConnectionPoint,
								real springConstant,
								real restLength);
		~AnchoredSpring() = default;

		/**
		* \brief Apply force to a rigid body over a specific time.
		* \param body The rigid body on which to apply force.
		* \param duration The duration over which the force acts.
		*/
		void updateForce(RigidBody* body, real duration) override;

	protected:
		glm::vec3 m_connectionPoint;
		glm::vec3 m_anchor;
		real m_springConstant;
		real m_restLength;
	};
}
