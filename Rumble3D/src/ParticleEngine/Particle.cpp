#include "R3D/ParticleEngine/Particle.h"
#include <cmath>
#include <cassert>

namespace rum 
{
	Particle::Particle()
		: m_position{real(0)},
		m_velocity{real(0)},
		m_acceleration{real(0)},
		m_forceAccumulator{real(0)},
		m_inverseMass{0},
		m_damping{1},
		m_isDead{false}
	{
	}

	Particle::~Particle()
	= default;

	void Particle::setMass(const real mass)
	{
		assert(mass != 0);
		m_inverseMass = (static_cast<real>(1.0)) / mass;
	}

	real Particle::getMass() const
	{
		if (m_inverseMass == 0) 
		{
			return EROS_REAL_MAX;
		}
		return (static_cast<real>(1.0)) / m_inverseMass;
	}

	void Particle::setInverseMass(const real inverseMass)
	{
		m_inverseMass = inverseMass;
	}

	real Particle::getInverseMass() const
	{
		return m_inverseMass;
	}

	bool Particle::hasFiniteMass() const
	{
		return m_inverseMass > 0.0f;
	}

	const glm::vec3& Particle::getForceAccumulator() const
	{
		return m_forceAccumulator;
	}

	void Particle::setDamping(const real damping)
	{
		m_damping = damping;
	}

	real Particle::getDamping() const
	{
		return m_damping;
	}

	void Particle::setPosition(const glm::vec3 &position)
	{
		m_position = position;
	}

	void Particle::setPosition(const real x, const real y, const real z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	const glm::vec3& Particle::getPosition() const
	{
		return m_position;
	}

	void Particle::setVelocity(const glm::vec3 &velocity)
	{
		m_velocity = velocity;
	}

	void Particle::setVelocity(const real x, const real y, const real z)
	{
		m_velocity.x = x;
		m_velocity.y = y;
		m_velocity.z = z;
	}

	const glm::vec3& Particle::getVelocity() const
	{
		return m_velocity;
	}

	void Particle::setAcceleration(const glm::vec3 &acceleration)
	{
		m_acceleration = acceleration;
	}

	void Particle::setAcceleration(const real x, const real y, const real z)
	{
		m_acceleration.x = x;
		m_acceleration.y = y;
		m_acceleration.z = z;
	}

	const glm::vec3& Particle::getAcceleration() const
	{
		return m_acceleration;
	}

	void Particle::setIsDead(bool isDead)
	{
		m_isDead = isDead;
	}

	bool Particle::isDead() const
	{
		return m_isDead;
	}

	void Particle::clearAccumulator()
	{
		m_forceAccumulator = glm::vec3(0.0f);
	}

	void Particle::addForce(const glm::vec3 &force)
	{
		m_forceAccumulator += force;
	}

	void Particle::integrate(const real duration) 
	{
		if (m_isDead || m_inverseMass <= 0) return;

		assert(duration > 0.0);

		// Neue Position bestimmen:
		// Hier quadratischer Term aus der Beschleunigung nicht berücksichtigt, da marginal.
		m_position += m_velocity * duration;

		// Beschleunigung bestimmen:
		glm::vec3 resultingAcceleration = m_acceleration;
		resultingAcceleration += m_forceAccumulator * m_inverseMass;

		// Neue Geschwindigkeit durch die Beschleunigung:
		m_velocity += resultingAcceleration * duration;

		// Dämpfung berücksichtigen:
		m_velocity *= pow(m_damping, duration);

		clearAccumulator();
	}
}