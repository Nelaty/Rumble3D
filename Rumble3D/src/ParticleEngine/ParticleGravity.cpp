#include "R3D/ParticleEngine/ParticleGravity.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
	ParticleGravity::ParticleGravity(const glm::vec3& gravity)
		: m_gravity{gravity}
	{
	}

	void ParticleGravity::updateForce(Particle* particle, real duration)
	{
		if(!particle->hasFiniteMass()) return;

		// The mass factor is necessary, since it will be nullified later on
		// by inverse mass multiplication in the integration step.
		particle->addForce(m_gravity * particle->getMass());
	}

	const glm::vec3& ParticleGravity::getGravity() const
	{
		return m_gravity;
	}

	void ParticleGravity::setGravity(const glm::vec3& gravity)
	{
		m_gravity = gravity;
	}
}