#include "R3D/ParticleEngine/ParticleForceRegistry.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleForceGenerator.h"

namespace r3
{
	void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator * fg)
	{
		auto i = m_registrations.begin();
		for (; i != m_registrations.end(); ++i)
		{
			if (i->m_particle == particle && i->m_forceGenerator == fg)
			{
				m_registrations.erase(i);
			}
		}
	}
	
	
	void ParticleForceRegistry::clear()
	{
		m_registrations.clear();
	}
	
	void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator * fg)
	{
		ParticleForceRegistrationEntry registration{};
		registration.m_particle = particle;
		registration.m_forceGenerator = fg;
		m_registrations.push_back(registration);
	}
	
	
	void ParticleForceRegistry::updateForces(const real duration)
	{
		for(auto& it : m_registrations)
		{
			it.m_forceGenerator->updateForce(it.m_particle, duration);
		}
	}
}
