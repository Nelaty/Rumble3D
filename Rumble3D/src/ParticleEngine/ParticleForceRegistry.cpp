#include "R3D/ParticleEngine/ParticleForceRegistry.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleForceGenerator.h"

namespace rum
{
	void ParticleForceRegistry::Remove(Particle* particle, ParticleForceGenerator * fg)
	{
		Registry::iterator i = registrations.begin();
		for (; i != registrations.end(); i++)
		{
			if (i->particle == particle && i->forceGenerator == fg)
			{
				registrations.erase(i);
			}
		}
	}
	
	
	void ParticleForceRegistry::Clear()
	{
		registrations.clear();
	}
	
	void ParticleForceRegistry::Add(Particle * particle, ParticleForceGenerator * fg)
	{
		ParticleForceRegistrationEntry registration;
		registration.particle = particle;
		registration.forceGenerator = fg;
		registrations.push_back(registration);
	}
	
	
	void ParticleForceRegistry::UpdateForces(real duration)
	{
		for(auto& it : registrations)
		{
			it.forceGenerator->UpdateForce(it.particle, duration);
		}
	}
}
