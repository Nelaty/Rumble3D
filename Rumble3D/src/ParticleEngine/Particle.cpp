#include "R3D/ParticleEngine/Particle.h"

#include <cassert>
#include <stdexcept>

namespace r3
{
	Particle::Particle()
	{
		init(ParticleDef());
	}

	Particle::Particle(const ParticleDef& definition)
	{
		init(definition);
	}

	void Particle::init(const ParticleDef& definition)
	{
		m_position = definition.m_position;
		m_velocity = definition.m_velocity;
		m_acceleration = definition.m_acceleration;
		m_forceAccumulator = definition.m_forceAccumulator;
		m_damping = definition.m_damping;
		m_inverseMass = definition.m_inverseMass;
		m_isDead = definition.m_isDead;
	}

	void Particle::setMass(const real mass)
	{
	    if(mass <= 0) throw std::invalid_argument("mass must be > 0");
		m_inverseMass = real(1) / mass;
	}

	real Particle::getMass() const
	{
		if (m_inverseMass == 0)
		{
			return R3D_REAL_MAX;
		}
		return real(1) / m_inverseMass;
	}

	void Particle::setInverseMass(const real inverseMass)
	{
	    if(inverseMass < 0) throw std::invalid_argument("inverse mass must be positive");
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

	void Particle::setVelocity(const glm::vec3& velocity)
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

	void Particle::setAcceleration(const glm::vec3& acceleration)
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

	void Particle::setIsDead(const bool isDead)
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

	void Particle::addForce(const glm::vec3& force)
	{
		m_forceAccumulator += force;
	}

	void Particle::reset(const glm::vec3& position)
	{
		m_position = position;
		m_velocity = glm::vec3(0);
		m_acceleration = glm::vec3(0);
		m_isDead = false;
		clearAccumulator();
	}

	void Particle::integrate(const real duration)
	{
	    if(m_isDead || m_inverseMass <= 0)
        {
	        clearAccumulator();
	        return;
        }

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

    bool Particle::operator==(const Particle& rhs) const
    {
	    return rhs.m_position == m_position
	        && rhs.m_velocity == m_velocity
	        && rhs.m_acceleration == m_acceleration
	        && rhs.m_forceAccumulator == m_forceAccumulator
	        && rhs.m_damping == m_damping
	        && rhs.m_inverseMass == m_inverseMass
	        && rhs.m_isDead == m_isDead;
    }
}