#include "R3D/RigidBodyEngine/DirectedForce.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include <glm/gtc/quaternion.hpp>

namespace r3
{
	DirectedForce::DirectedForce(const glm::vec3& localPosition, 
								 const glm::vec3& force)
		: m_force{force},
		m_localPosition{localPosition}
	{
	}

	void DirectedForce::updateForce(RigidBody* body, real duration)
	{
		const auto attackPoint = m_localPosition;
		auto forceLocal = m_force;
		const auto quaternion = body->getOrientation();
	
		// Rotate forceLocal by quaternion
		forceLocal = quaternion * forceLocal;

		/// \todo: add force at body point doesn't create rotational forces.
		body->addForceAtBodyPoint(forceLocal, attackPoint);
		body->addRotation(forceLocal);
	}

	void DirectedForce::setForce(const glm::vec3& force)
	{
		m_force = force;
	}	
}