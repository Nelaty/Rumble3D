#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleEngineCI.h"

#include <algorithm>

namespace rum
{
	ParticleWorld::ParticleWorld()
	= default;

	ParticleWorld::~ParticleWorld()
	= default;

	void ParticleWorld::setComputationInterface(ParticleEngineCI* computationInterface)
	{
		m_computationInterface = computationInterface;
	}

	IComputationInterface* ParticleWorld::getComputationInterface() const
	{
		return m_computationInterface;
	}
	
	void ParticleWorld::registerParticle(Particle* p)
	{
		m_particles.push_back(p);
	}
	
	void ParticleWorld::unregisterParticle(Particle* p)
	{
		std::remove(m_particles.begin(), m_particles.end(), p);
	}
	
	void ParticleWorld::unregisterAllParticles()
	{
		m_particles.clear();
	}
	
	rum::ParticleForceRegistry& ParticleWorld::getParticleForceRegistry()
{
		return m_forceRegistry;
	}

	const ParticleForceRegistry& ParticleWorld::getParticleForceRegistry() const
	{
		return m_forceRegistry;
	}

	ParticleWorld::Particles& ParticleWorld::getParticles()
	{
		return m_particles;
	}

	const ParticleWorld::Particles& ParticleWorld::getParticles() const
	{
		return m_particles;
	}

	ParticleContactGeneratorRegistry& ParticleWorld::getContactGeneratorRegistry()
	{
		return m_contactGeneratorRegistry;
	}

	const ParticleContactGeneratorRegistry& ParticleWorld::getContactGeneratorRegistry() const
	{
		return m_contactGeneratorRegistry;
	}
}
