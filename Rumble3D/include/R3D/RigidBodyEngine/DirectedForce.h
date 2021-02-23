#pragma once
#include "ForceGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	/**
	 * \brief A DirectedForce is a force generator, which will continually
	 * apply a specified force at a specific body point.
	 */
	class R3D_DECLSPEC DirectedForce : public ForceGenerator
	{
	public:
		/**
		 * \brief DirectedForce constructor.
		 * \param localPosition Attack point of the force.
		 * \param force The force, which will act on the body.
		 */
		DirectedForce(const glm::vec3& localPosition, 
					  const glm::vec3& force);
		~DirectedForce() = default;

		/**
		* \brief Apply force to a rigid body over a specific time.
		* \param body The rigid body on which to apply force.
		* \param duration The duration over which the force acts.
		*/
		void updateForce(RigidBody* body, real duration) override;

		/**
		 * \brief Set the force, which will act on the body.
		 * \param force The new force. 
		 */
		void setForce(const glm::vec3& force);
		
	private:
		glm::vec3 m_force;
		glm::vec3 m_localPosition;
	};
}
