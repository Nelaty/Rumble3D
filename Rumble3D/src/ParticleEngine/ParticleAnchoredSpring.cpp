#include "R3D/ParticleEngine/ParticleAnchoredSpring.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
	ParticleAnchoredSpring::ParticleAnchoredSpring(glm::vec3* anchor, real springConstant, real restLength)
		: m_anchor{anchor},
		m_springConstant{springConstant},
		m_restLength{restLength}
	{
	}

	void ParticleAnchoredSpring::updateForce(Particle* particle)
	{
		// Calculate distance vector
		auto force = particle->getPosition();
		force -= *m_anchor;

		// Calculate distance
		auto magnitude = glm::length(force);
		if(magnitude == real(0)) return;

		// Force only acts at a different distance than the resting length
		magnitude -= m_restLength;
		// A firm spring (higher constant) is more sensitive to changes in
		// the resting length
		magnitude *= m_springConstant;

		force = glm::normalize(force);
		force *= -magnitude;
		particle->addForce(force);
	}
}