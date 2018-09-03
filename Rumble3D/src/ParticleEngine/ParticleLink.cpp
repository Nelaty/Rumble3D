#include "R3D/ParticleEngine/ParticleLink.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <glm/glm.hpp>

namespace r3
{
	real ParticleLink::currentLength() const 
	{
		const auto distance = m_particles[0]->getPosition() - m_particles[1]->getPosition();
		return glm::length(distance);
	}

	ParticleLink::~ParticleLink()
	= default;

	void ParticleLink::setParticles(Particle* particle0, Particle* particle1)
	{
		m_particles[0] = particle0;
		m_particles[1] = particle1;
	}

	ParticleLink::ParticleLink()
	= default;
}
