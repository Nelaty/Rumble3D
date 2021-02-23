#include "R3D/ParticleEngine/ParticleLink.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <glm/glm.hpp>

namespace r3
{
	void ParticleLink::setParticles(Particle* first, Particle* second)
	{
		m_particles[0] = first;
		m_particles[1] = second;
	}

	Particle* ParticleLink::getFirst() const
	{
		return m_particles[0];
	}

	Particle* ParticleLink::getSecond() const
	{
		return m_particles[1];
	}

	real ParticleLink::currentLength() const
	{
		assert(m_particles[0] && m_particles[1]);

		const auto distance = m_particles[0]->getPosition() - m_particles[1]->getPosition();
		return glm::length(distance);
	}
}
