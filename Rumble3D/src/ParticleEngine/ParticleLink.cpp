#include "R3D/ParticleEngine/ParticleLink.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <glm/glm.hpp>

namespace rum
{
	real ParticleLink::currentLength() const 
	{
		glm::vec3 distance = m_particles[0]->GetPosition() - m_particles[1]->GetPosition();
		return glm::length(distance);
	}
	
	void ParticleLink::setParticles(Particle* particle0, Particle* particle1)
	{
		m_particles[0] = particle0;
		m_particles[1] = particle1;
	}
}