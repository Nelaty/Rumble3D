#include "R3D/ParticleEngine/ParticleBungee.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleBungee::ParticleBungee(Particle* other, real springConstant, real restLength)
	{
		m_other = other;
		m_springConstant = springConstant;
		m_restLength = restLength;
	}
	
	
	ParticleBungee::~ParticleBungee()
	= default;

	void ParticleBungee::updateForce(Particle* particle, real duration)
	{
		glm::vec3 force = particle->getPosition();
		force -= m_other->getPosition();
	
		real magnitude = glm::length(force);
		if(magnitude <= m_restLength)
		{
			return;
		}
	
		magnitude = m_springConstant * (m_restLength - magnitude);
	
		force = glm::normalize(force);
		force *= magnitude;
		particle->addForce(force);
	}
}