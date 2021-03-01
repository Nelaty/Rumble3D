#include "R3D/ParticleEngine/ParticleForceRegistry.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"

#include <algorithm>

namespace r3
{
	void ParticleForceRegistry::remove(Particle* particle, IParticleForceGenerator * generator)
	{
	    m_registrations.erase(
	        std::remove_if(m_registrations.begin(),
	            m_registrations.end(),
               [&](const ParticleForceRegistrationEntry& entry)
               {
                   return entry.m_particle == particle
                       && entry.m_forceGenerator == generator;
               }),
            m_registrations.end());
	}
	
	void ParticleForceRegistry::clear()
	{
		m_registrations.clear();
	}

	void ParticleForceRegistry::add(Particle* particle, IParticleForceGenerator * generator)
	{
		m_registrations.emplace_back(ParticleForceRegistrationEntry{particle, generator});
	}
	
	void ParticleForceRegistry::updateForces()
	{
		for(auto& it : m_registrations)
		{
			it.m_forceGenerator->updateForce(it.m_particle);
		}
	}
}
