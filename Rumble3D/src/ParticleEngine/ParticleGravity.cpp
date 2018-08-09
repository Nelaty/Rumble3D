#include "R3D/ParticleEngine/ParticleGravity.h"
#include "R3D/ParticleEngine/Particle.h"

namespace rum
{
	ParticleGravity::ParticleGravity(const glm::vec3& gravity)
		: m_gravity{gravity}
	{
	}
	
	
	void ParticleGravity::UpdateForce(Particle* particle, real duration)
	{
		if(!particle->HasFiniteMass())
		{
			return;
		}
		particle->AddForce(m_gravity * particle->GetMass());
	}
}