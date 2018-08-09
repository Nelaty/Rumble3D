#include "R3D/RigidBodyEngine/DirectedForce.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include <glm/gtc/quaternion.hpp>

namespace rum
{
	DirectedForce::DirectedForce(glm::vec3 localPosition, glm::vec3 force)
		: m_force{force},
		m_localPosition{localPosition}
	{
	}
	
	DirectedForce::~DirectedForce()
	{
	}
	
	void DirectedForce::UpdateForce(RigidBody* body, real duration)
	{
		glm::vec3 attackPoint = m_localPosition;
		glm::vec3 forceLocal = m_force;
		auto quat = body->getOrientation();
	
		// Rotate forceLocal by quaternion
		forceLocal = quat * forceLocal;

		body->addForceAtBodyPoint(forceLocal, attackPoint);
		body->addRotation(forceLocal);
	}

	void DirectedForce::SetForce(const glm::vec3& force)
	{
		m_force = force;
	}	
}