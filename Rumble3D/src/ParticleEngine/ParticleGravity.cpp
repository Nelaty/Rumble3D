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

	void ParticleGravity::updateForce(Particle* particle)
	{
		if(!particle->hasFiniteMass()) return;

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