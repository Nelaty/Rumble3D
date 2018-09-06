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

	Particle* ParticleWorld::createParticle(const ParticleDef definition)
	{
		auto particle = new Particle(definition);
		m_particles.emplace_back(particle);
		return particle;
	}

	bool ParticleWorld::destroyParticle(Particle* particle)
	{
		const auto removedParticle = std::remove(m_particles.begin(),
												 m_particles.end(),
												 particle);

		if(removedParticle != m_particles.end())
		{
			delete *removedParticle;
			return true;
		}
		return false;
	}

	void ParticleWorld::destroyAllParticles()
	{
		for(auto& it : m_particles)
		{
			delete it;
		}
		m_particles.clear();
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
