#include "R3D/ParticleEngine/ParticleBuoyancy.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleBuoyancy::ParticleBuoyancy(const real maxDepth,
									   const real volume,
									   const real liquidHeight,
									   const real liquidDensity,
									   const real gravity)
	{
		m_maxDepth = maxDepth;
		m_volume = volume;
		m_liquidHeight = liquidHeight;
		m_liquidDensity = liquidDensity;
		m_gravity = gravity;
	}
	
	ParticleBuoyancy::~ParticleBuoyancy()
	= default;

	void ParticleBuoyancy::updateForce(Particle* particle, real duration)
	{
		const auto depth = particle->getPosition().y;
		const auto halfMaxDepth = m_maxDepth / 2;
	
		// Above water surface
		if(depth >= m_liquidHeight + halfMaxDepth) 
		{ 
			return; 
		}
	
		// Completely submerged
		const auto verticalForce = m_liquidDensity * m_volume * m_gravity;

		glm::vec3 force(real(0.0f));
		if (depth <= m_liquidHeight - halfMaxDepth) 
		{
			force.y = verticalForce;
			particle->addForce(force);
			return;
		}
	
		// Partly submerged
		const auto submergedDistance = m_liquidHeight - depth + halfMaxDepth;
		force.y = verticalForce * submergedDistance / m_maxDepth;
		particle->addForce(force);
	}
}