#include "R3D/ParticleEngine/ParticleForceRegistry.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"

#include <algorithm>

namespace r3
{
	ParticleForceRegistry::ParticleForceRegistry()
	{
	}

	ParticleForceRegistry::~ParticleForceRegistry()
	{
	}

	bool ParticleForceRegistry::remove(Particle* particle, IParticleForceGenerator * generator)
	{
		const auto removedItem = std::remove_if(m_registrations.begin(),
												m_registrations.end(),
												[&](const ParticleForceRegistrationEntry& entry)
		{
			return entry.m_particle == particle
				&& entry.m_forceGenerator == generator;
		});

		bool found = removedItem != m_registrations.end();
		m_registrations.erase(removedItem, m_registrations.end());
		return found;		
	}
	
	void ParticleForceRegistry::clear()
	{
		m_registrations.clear();
	}

	void ParticleForceRegistry::add(Particle* particle, IParticleForceGenerator * generator)
	{
		m_registrations.push_back(ParticleForceRegistrationEntry{particle, generator});
	}
	
	void ParticleForceRegistry::updateForces(const real duration)
	{
		for(auto& it : m_registrations)
		{
			it.m_forceGenerator->updateForce(it.m_particle, duration);
		}
	}
}
