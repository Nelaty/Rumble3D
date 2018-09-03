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

	ParticleAnchoredSpring::~ParticleAnchoredSpring()
	= default;

	void ParticleAnchoredSpring::updateForce(Particle* particle, real duration)
	{
		auto force = particle->getPosition();
		force -= *m_anchor;

		auto magnitude = glm::length(force);
		magnitude = (m_restLength - magnitude) * m_springConstant;

		force = glm::normalize(force);
		force *= magnitude;
		particle->addForce(force);
	}
}