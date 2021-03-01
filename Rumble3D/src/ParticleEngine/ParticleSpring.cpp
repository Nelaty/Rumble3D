#include "R3D/ParticleEngine/ParticleSpring.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleSpring::ParticleSpring(Particle* other,
								   const real springConstant,
								   const real restLength)
		: ParticleSpringBase(springConstant, restLength),
		m_other{other}
	{
	}


	void ParticleSpring::updateForce(Particle* particle)
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