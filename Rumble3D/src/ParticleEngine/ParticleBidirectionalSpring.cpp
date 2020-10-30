#include "R3D/ParticleEngine/ParticleBidirectionalSpring.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleBidirectionalSpring::ParticleBidirectionalSpring(Particle* other, 
															 const real springConstant, 
															 const real restLength)
		: ParticleSpringBase(springConstant, restLength),
		m_other(other)
	{
	}

	void ParticleBidirectionalSpring::updateForce(Particle* particle)
	{
		real magnitude;
		glm::vec3 distance;
		if(isMagnitudeValid(particle->getPosition(),
							m_other->getPosition(),
							distance,
							magnitude))
		{
			glm::vec3 force = real(0.5) * calculateForce(distance, magnitude);
			particle->addForce(force);
			m_other->addForce(-force);
		}
	}
}
