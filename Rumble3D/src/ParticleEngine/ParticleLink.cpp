#include "R3D/ParticleEngine/ParticleLink.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <glm/glm.hpp>

namespace r3
{
	void ParticleLink::setParticles(Particle* first, Particle* second)
	{
	    m_particles.first = first;
	    m_particles.second = second;
	}

	Particle* ParticleLink::getFirst() const
	{
	    return m_particles.first;
	}

	Particle* ParticleLink::getSecond() const
	{
	    return m_particles.second;
	}

	real ParticleLink::currentLength() const
	{
	    assert(m_particles.first && m_particles.second);

		const auto distance = m_particles.first->getPosition() - m_particles.second->getPosition();
		return glm::length(distance);
	}
}
