#include "R3D/RigidBodyEngine/AnchoredSpring.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	AnchoredSpring::AnchoredSpring(const glm::vec3& anchor,
								   const glm::vec3& localConnectionPoint,
								   real springConstant,
								   real restLength) 
		: m_connectionPoint(localConnectionPoint),
		m_anchor(anchor),
		m_springConstant(springConstant),
		m_restLength(restLength)
	{
	}

	void AnchoredSpring::updateForce(RigidBody* body, const real duration)
	{
		// Beide Enden der Feder in Weltkoordinaten:
		const auto localW = body->getPointInWorldSpace(m_connectionPoint);
		auto force = localW - m_anchor;

		// Betrag der Kraft:
		auto magnitude = glm::length(force);
		magnitude = abs(magnitude - m_restLength);
		magnitude *= m_springConstant;
	
		force = glm::normalize(force);
		force *= -magnitude;
		body->addForceAtPoint(force, localW);
	}
}
