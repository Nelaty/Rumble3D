#include "R3D/ParticleEngine/ParticleAnchoredSpring.h"
#include "R3D/ParticleEngine/Particle.h"

namespace rum
{
	ParticleAnchoredSpring::ParticleAnchoredSpring(glm::vec3* anchor, real springConstant, real restLength)
		: m_anchor{anchor},
		m_springConstant{springConstant},
		m_restLength{restLength}
	{
	}

	ParticleAnchoredSpring::~ParticleAnchoredSpring()
	{
	}

	void ParticleAnchoredSpring::UpdateForce(Particle* particle, real duration)
	{
		glm::vec3 force = particle->GetPosition();
		force -= *m_anchor;

		real magnitude = glm::length(force);
		magnitude = (m_restLength - magnitude) * m_springConstant;

		force = glm::normalize(force);
		force *= magnitude;
		particle->AddForce(force);
	}
}