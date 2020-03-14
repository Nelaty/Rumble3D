#pragma once
#include "R3D/RigidBodyEngine/ForceGenerator.h"

#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	/**
	* \brief A Spring is a force generator, which simulates a spring 
	* between two rigid bodies.
	* \details The spring force will not be applied to the rigid body,
	* which is assigned to this generator.
	*/
	class R3D_DECLSPEC Spring : public ForceGenerator
	{
	public:
		/**
		 * \brief Spring constructor.
		 * \param localConnectionPoint Connection point in local 
		 * coordinates of the body, which receives forces.
		 * \param other The other rigid body connected to the string.
		 * \param otherConnectionPoint Connection point in local
		 * coordinates of the other body.
		 * \param springConstant The hardness of the spring.
		 * \param restLength The distance at which no forces act.
		 */
		Spring(const glm::vec3& localConnectionPoint,
			   RigidBody* other,
			   const glm::vec3& otherConnectionPoint,
			   real springConstant,
			   real restLength);

		/**
		* \brief Apply force to a rigid body over a specific time.
		* \param body The rigid body on which to apply force.
		*/
		void updateForce(RigidBody* body) override;

	protected:
		real m_springConstant;
		real m_restLength;

		glm::vec3 m_connectionPoint;
		glm::vec3 m_otherConnectionPoint;

		RigidBody* m_other;
	};
}