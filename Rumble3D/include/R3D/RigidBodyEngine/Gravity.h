#pragma once
#include "ForceGenerator.h"

#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

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
		~Gravity();

		/**
		* \brief Apply force to a rigid body over a specific time.
		* \param body The rigid body on which to apply force.
		*/
		void updateForce(RigidBody* body) override;
	
	protected:
		glm::vec3 m_gravity;
	};
}