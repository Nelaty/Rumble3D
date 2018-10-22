#include "R3D/ParticleEngine/ParticleForceRegistry.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"


namespace r3
{
	void ParticleForceRegistry::remove(Particle* particle, IParticleForceGenerator * generator)
	{
		for (auto i = m_registrations.begin(); i != m_registrations.end(); ++i)
		{
			if (i->m_particle == particle && i->m_forceGenerator == generator)
			{
				m_registrations.erase(i);
			}
		}
	}
	
	void ParticleForceRegistry::clear()
	{
		m_registrations.clear();
	}
	
	void ParticleForceRegistry::add(Particle* particle, IParticleForceGenerator * generator)
	{
		m_registrations.push_back({particle, generator});
	}
	
	void ParticleForceRegistry::updateForces(const real duration)
	{
		for(auto& it : m_registrations)
		{
			it.m_forceGenerator->updateForce(it.m_particle, duration);
		}
	}
}
