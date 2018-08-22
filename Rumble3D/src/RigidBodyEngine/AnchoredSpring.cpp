#include "R3D/RigidBodyEngine/AnchoredSpring.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace rum
{
	AnchoredSpring::AnchoredSpring(const glm::vec3& anchor,
								   const glm::vec3& localConnectionPoint,
								   real springConstant,
								   real restLength) 
		: m_anchor(anchor),
		m_connectionPoint(localConnectionPoint),
		m_springConstant(springConstant),
		m_restLength(restLength)
	{
	}
	
	void AnchoredSpring::updateForce(RigidBody* body, real duration)
	{
		// Beide Enden der Feder in Weltkoordinaten:
		glm::vec3 localW = body->getPointInWorldSpace(m_connectionPoint);
		glm::vec3 force = localW - m_anchor;

		// Betrag der Kraft:
		real magnitude = glm::length(force);
		magnitude = abs(magnitude - m_restLength);
		magnitude *= m_springConstant;
	
		force = glm::normalize(force);
		force *= -magnitude;
		body->addForceAtPoint(force, localW);
	}
}
