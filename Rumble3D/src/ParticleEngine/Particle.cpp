#include "R3D/ParticleEngine/Particle.h"

#include <cassert>


r3::Particle::Particle()
{
	init(ParticleDef());
}

r3::Particle::Particle(const ParticleDef& definition)
{
	init(definition);
}

r3::Particle::~Particle()
		= default;

void r3::Particle::init(const ParticleDef& definition)
{
	m_position = definition.m_position;
	m_velocity = definition.m_velocity;
	m_acceleration = definition.m_acceleration;
	m_forceAccumulator = definition.m_forceAccumulator;
	m_damping = definition.m_damping;
	m_inverseMass = definition.m_inverseMass;
	m_isDead = definition.m_isDead;
}

void r3::Particle::setMass(const real mass)
	{
		assert(mass != 0);
		m_inverseMass = (static_cast<real>(1.0)) / mass;
	}

r3::real r3::Particle::getMass() const
	{
		if(m_inverseMass == 0)
		{
			return R3D_REAL_MAX;
		}
		return (static_cast<real>(1.0)) / m_inverseMass;
	}

	void r3::Particle::setInverseMass(const real inverseMass)
	{
		m_inverseMass = inverseMass;
	}

r3::real r3::Particle::getInverseMass() const
	{
		return m_inverseMass;
	}

	bool r3::Particle::hasFiniteMass() const
	{
		return m_inverseMass > 0.0f;
	}

	const glm::vec3& r3::Particle::getForceAccumulator() const
	{
		return m_forceAccumulator;
	}

	void r3::Particle::setDamping(const real damping)
	{
		m_damping = damping;
	}

r3::real r3::Particle::getDamping() const
	{
		return m_damping;
	}

	void r3::Particle::setPosition(const glm::vec3 &position)
	{
		m_position = position;
	}

	void r3::Particle::setPosition(const real x, const real y, const real z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	const glm::vec3& r3::Particle::getPosition() const
	{
		return m_position;
	}

	void r3::Particle::setVelocity(const glm::vec3 &velocity)
	{
		m_velocity = velocity;
	}

	void r3::Particle::setVelocity(const real x, const real y, const real z)
	{
		m_velocity.x = x;
		m_velocity.y = y;
		m_velocity.z = z;
	}

	const glm::vec3& r3::Particle::getVelocity() const
	{
		return m_velocity;
	}

	void r3::Particle::setAcceleration(const glm::vec3 &acceleration)
	{
		m_acceleration = acceleration;
	}

	void r3::Particle::setAcceleration(const real x, const real y, const real z)
	{
		m_acceleration.x = x;
		m_acceleration.y = y;
		m_acceleration.z = z;
	}

	const glm::vec3& r3::Particle::getAcceleration() const
	{
		return m_acceleration;
	}

	void r3::Particle::setIsDead(const bool isDead)
	{
		m_isDead = isDead;
	}

	bool r3::Particle::isDead() const
	{
		return m_isDead;
	}

	void r3::Particle::clearAccumulator()
	{
		m_forceAccumulator = glm::vec3(0.0f);
	}

	void r3::Particle::addForce(const glm::vec3 &force)
	{
		m_forceAccumulator += force;
	}

	void r3::Particle::integrate(const real duration)
	{
		if(m_isDead || m_inverseMass <= 0) return;

		assert(duration > 0.0);

		// Update the position
		// Ignore quadratic term, since its effect is marginal
		m_position += m_velocity * duration;

		// Calculate the acceleration
		auto resultingAcceleration = m_acceleration;
		resultingAcceleration += m_forceAccumulator * m_inverseMass;

		// Update the velocity
		m_velocity += resultingAcceleration * duration;

		// Apply damping
		m_velocity *= pow(m_damping, duration);

		clearAccumulator();
	}
