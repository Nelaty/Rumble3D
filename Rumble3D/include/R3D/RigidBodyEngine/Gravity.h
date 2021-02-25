#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/RigidBodyEngine/ForceGenerator.h"

#include <glm/glm.hpp>

namespace r3 
{
	class RigidBody;

	/**
	 * \brief Gravity is a force generator, which will apply constant
	 * force on bodies.
	 */
	class R3D_DECLSPEC Gravity : public ForceGenerator
	{
	public:
		/**
		 * \brief Gravity constructor.
		 * \param gravity A constant force.
		 */
		explicit Gravity(const glm::vec3& gravity);
		~Gravity() = default;

		/**
		* \brief Apply force to a rigid body over a specific time.
		* \param body The rigid body on which to apply force.
		* \param duration The duration over which the force acts.
		*/
		void updateForce(RigidBody* body, real timeDelta) override;
	
	protected:
		glm::vec3 m_gravity;
	};
}