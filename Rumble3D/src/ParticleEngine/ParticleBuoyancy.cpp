#include "R3D/ParticleEngine/ParticleBuoyancy.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

#include <cassert>

namespace r3
{
	ParticleBuoyancy::ParticleBuoyancy(const real maxDepth,
									   const real volume,
									   const real liquidHeight,
									   const real liquidDensity,
									   const real gravity)
	{
		setMaxDepth(maxDepth);
		m_volume = volume;
		m_liquidHeight = liquidHeight;
		m_liquidDensity = liquidDensity;
		m_gravity = gravity;
	}
	
	ParticleBuoyancy::~ParticleBuoyancy()
	= default;

	void ParticleBuoyancy::updateForce(Particle* particle)
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

	r3::real ParticleBuoyancy::getMaxDepth() const
	{
		return m_maxDepth;
	}

	void ParticleBuoyancy::setMaxDepth(real depth)
	{
		assert(depth != real(0));
		m_maxDepth = depth;
	}

	r3::real ParticleBuoyancy::getVolume() const
	{
		return m_volume;
	}

	void ParticleBuoyancy::setVolume(real depth)
	{
		m_volume = depth;
	}

	r3::real ParticleBuoyancy::getLiquidHeight() const
	{
		return m_liquidHeight;
	}

	void ParticleBuoyancy::setLiquidHeight(real height)
	{
		m_liquidHeight = height;
	}

	r3::real ParticleBuoyancy::getLiquidDensity() const
	{
		return m_liquidDensity;
	}

	void ParticleBuoyancy::setLiquidDensity(real density)
	{
		m_liquidDensity = density;
	}

	r3::real ParticleBuoyancy::getGravity() const
	{
		return m_gravity;
	}

	void ParticleBuoyancy::setGravity(real gravity)
	{
		m_gravity = gravity;
	}

}