#include "R3D/ParticleEngine/ParticleBungee.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleBungee::ParticleBungee(Particle* other, real springConstant, real restLength)
		: ParticleSpringBase(springConstant, restLength),
		m_other(other)
	{
	}

	void ParticleBungee::updateForce(Particle* particle)
	{
		real magnitude;
		glm::vec3 distance;
		if(isMagnitudeValid(particle->getPosition(),
							m_other->getPosition(),
							distance,
							magnitude))
		{
			particle->addForce(calculateForce(distance, magnitude));
		}
	}
}