#include "R3D/ParticleEngine/ParticleAnchoredSpring.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
	ParticleAnchoredSpring::ParticleAnchoredSpring(glm::vec3* anchor, real springConstant, real restLength)
		: ParticleSpringBase(springConstant, restLength),
		m_anchor{anchor}
	{
	}

	void ParticleAnchoredSpring::updateForce(Particle* particle)
	{
		real magnitude;
		glm::vec3 distance;
		if(isMagnitudeValid(particle->getPosition(),
							*m_anchor,
							distance,
							magnitude))
		{
			particle->addForce(calculateForce(distance, magnitude));
		}
	}
}