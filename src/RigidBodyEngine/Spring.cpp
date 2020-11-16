#include "R3D/RigidBodyEngine/Spring.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	Spring::Spring(const glm::vec3& localConnectionPoint,
				   RigidBody* other,
				   const glm::vec3& otherConnectionPoint,
				   real springConstant,
				   real restLength) 
		: m_springConstant(springConstant),
		m_restLength(restLength),
		m_connectionPoint(localConnectionPoint),
		m_otherConnectionPoint(otherConnectionPoint),
		m_other(other)
	{
	}
	
	void Spring::updateForce(RigidBody* body, real duration)
	{
		// Beide Enden der Feder in Weltkoordinaten:
		glm::vec3 localW = body->getPointInWorldSpace(m_connectionPoint);
		glm::vec3 otherW = m_other->getPointInWorldSpace(m_otherConnectionPoint);
		glm::vec3 force = localW - otherW;

		// Betrag der Kraft:
		real magnitude = glm::length(force);
		magnitude = abs(magnitude - m_restLength);
		magnitude *= m_springConstant;
	
		force = glm::normalize(force);
		force *= -magnitude;
		body->addForceAtPoint(force, localW);
	}
}
