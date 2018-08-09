#include "R3D/ParticleEngine/Particle.h"
#include <math.h>
#include <assert.h>

#include <glm/gtc/constants.hpp>

namespace rum 
{
	Particle::Particle()
		: m_position{real(0)},
		m_velocity{real(0)},
		m_acceleration{real(0)},
		m_forceAccum{real(0)},
		m_inverseMass{0},
		m_damping{1},
		m_isDead{false}
	{
	}

	Particle::~Particle()
	{
	}

	void Particle::SetMass(const real mass)
	{
		assert(mass != 0);
		Particle::m_inverseMass = (static_cast<real>(1.0)) / mass;
	}

	real Particle::GetMass() const
	{
		if (m_inverseMass == 0) 
		{
			return EROS_REAL_MAX;
		}
		else 
		{
			return (static_cast<real>(1.0)) / m_inverseMass;
		}
	}

	void Particle::SetInverseMass(const real inverseMass)
	{
		Particle::m_inverseMass = inverseMass;
	}

	real Particle::GetInverseMass() const
	{
		return m_inverseMass;
	}

	bool Particle::HasFiniteMass()
	{
		return m_inverseMass > 0.0f;
	}

	const glm::vec3& Particle::GetForceAccum()
	{
		m_forceAccum += m_forceAccum * m_inverseMass;
		return m_forceAccum;
	}

	void Particle::SetDamping(const real damping)
	{
		Particle::m_damping = damping;
	}

	real Particle::GetDamping() const
	{
		return m_damping;
	}

	void Particle::SetPosition(const glm::vec3 &position)
	{
		Particle::m_position = position;
	}

	void Particle::SetPosition(const real x, const real y, const real z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	const glm::vec3& Particle::GetPosition() const
	{
		return m_position;
	}

	void Particle::SetVelocity(const glm::vec3 &velocity)
	{
		Particle::m_velocity = velocity;
	}

	void Particle::SetVelocity(const real x, const real y, const real z)
	{
		m_velocity.x = x;
		m_velocity.y = y;
		m_velocity.z = z;
	}

	const glm::vec3& Particle::GetVelocity() const
	{
		return m_velocity;
	}

	void Particle::SetAcceleration(const glm::vec3 &acceleration)
	{
		Particle::m_acceleration = acceleration;
	}

	void Particle::SetAcceleration(const real x, const real y, const real z)
	{
		m_acceleration.x = x;
		m_acceleration.y = y;
		m_acceleration.z = z;
	}

	const glm::vec3& Particle::GetAcceleration() const
	{
		return m_acceleration;
	}

	void Particle::SetIsDead(bool isDead)
	{
		m_isDead = isDead;
	}

	bool Particle::IsDead()
	{
		return m_isDead;
	}

	void Particle::ClearAccumulator()
	{
		m_forceAccum = glm::vec3(0.0f);
	}

	void Particle::AddForce(const glm::vec3 &force)
	{
		m_forceAccum += force;
	}

	void Particle::Integrate(real duration) 
	{
		if (m_isDead || m_inverseMass <= 0) return;

		assert(duration > 0.0);

		//Neue Position bestimmen:
		//Hier quadratischer Term aus der Beschleunigung nicht berücksichtigt, da marginal.
		m_position += m_velocity * duration;

		//Beschleunigung bestimmen:
		glm::vec3 resultingAcceleration = m_acceleration;
		resultingAcceleration += m_forceAccum * m_inverseMass;

		//Neue Geschwindigkeit durch die Beschleunigung:
		m_velocity += resultingAcceleration * duration;

		//Dämpfung berücksichtigen:
		m_velocity *= pow(m_damping, duration);

		ClearAccumulator();
	}
}