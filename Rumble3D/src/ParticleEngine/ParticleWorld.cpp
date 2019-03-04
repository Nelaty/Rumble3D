#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleEngineCI.h"

#include <algorithm>

namespace r3
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

	void ParticleWorld::addParticle(Particle* particle)
	{
		m_particles.push_back(particle);
	}

	bool ParticleWorld::removeParticle(Particle* particle)
	{
		const auto removedParticle = std::remove(m_particles.begin(),
												 m_particles.end(),
												 particle);

		return removedParticle != m_particles.end();
	}

	r3::ParticleForceRegistry& ParticleWorld::getParticleForceRegistry()
{
		return m_forceRegistry;
	}

	const ParticleForceRegistry& ParticleWorld::getParticleForceRegistry() const
	{
		return m_forceRegistry;
	}

	ParticleWorld::Particle_Container& ParticleWorld::getParticles()
	{
		return m_particles;
	}

	const ParticleWorld::Particle_Container& ParticleWorld::getParticles() const
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
