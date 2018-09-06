#include "R3D/ParticleEngine/ParticleBuoyancy.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real liquidHeight, real liquidDensity)
	{
		m_maxDepth = maxDepth;
		m_volume = volume;
		m_liquidHeight = liquidHeight;
		m_liquidDensity = liquidDensity;
	}
	
	
	ParticleBuoyancy::~ParticleBuoyancy()
	= default;

	void ParticleBuoyancy::updateForce(Particle* particle, real duration)
	{
		real depth = particle->getPosition().y;
		real halfMaxDepth = m_maxDepth / 2;
	
		// Above water surface
		if(depth >= m_liquidHeight + halfMaxDepth) 
		{ 
			return; 
		}
	
		// Completely submerged
		glm::vec3 force(real(0.0f));
		if (depth <= m_liquidHeight - halfMaxDepth) 
		{
			force.y = m_liquidDensity * m_volume * 9.81f;
			particle->addForce(force);
			return;
		}
	
		// Partly submerged
		force.y = (m_liquidDensity * m_volume * 9.81 * (m_liquidHeight - depth + halfMaxDepth) / m_maxDepth);
		particle->addForce(force);
	}
}