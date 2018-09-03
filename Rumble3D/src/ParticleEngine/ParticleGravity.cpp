#include "R3D/ParticleEngine/ParticleGravity.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
	ParticleGravity::ParticleGravity(const glm::vec3& gravity)
		: m_gravity{gravity}
	{
	}

	ParticleGravity::~ParticleGravity()
	= default;

	void ParticleGravity::updateForce(Particle* particle, real duration)
	{
		if(!particle->hasFiniteMass())
		{
			return;
		}
		particle->addForce(m_gravity * particle->getMass());
	}
}