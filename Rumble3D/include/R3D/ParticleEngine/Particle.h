#pragma once
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum 
{
	class Particle 
	{
	public:
		explicit Particle();
		virtual ~Particle();

		/**
		 * Change the mass of this particle to the given given value. 
		 * Implicitly changes inverse mass.
		 */
		void SetMass(const real mass);
		/** Get the current mass of this particle. */
		real GetMass() const;
		/** 
		 * Change the inverse mass of this particle to the given value.
		 * Implicitly changes mass.
		 * \param inverseMass A value of 0 is equivalent to infinite mass.
		 */
		void SetInverseMass(const real inverseMass);
		/**
		 * Get the current inverse mass of this particle
		 * If particle has infinite mass, inverse mass will be 0.
		 */
		real GetInverseMass() const;
		/**
		 * Check if this particle has infinite mass.
		 * \return True if mass is infinite.
		 */
		bool HasFiniteMass();

		/** Change particle position to given vector. */
		void SetPosition(const glm::vec3 &position);
		/** Change particle position to given coordinates. */
		void SetPosition(const real x, const real y, const real z);
		/** Get the current position of this particle. */
		const glm::vec3& GetPosition() const;

		/** Change the current velocity of this particle to the given velocity. */
		void SetVelocity(const glm::vec3 &velocity);
		/** Change the current velocity of this particle to the given velocity. */
		void SetVelocity(const real x, const real y, const real z);
		/** Get the current velocity of this particle. */
		const glm::vec3& GetVelocity() const;

		/** Change the current acceleration of this particle to the given acceleration. */
		void SetAcceleration(const glm::vec3 &acceleration);
		/** Change the current acceleration of this particle to the given acceleration. */
		void SetAcceleration(const real x, const real y, const real z);
		/** Get the current acceleration of this particle. */
		const glm::vec3& GetAcceleration() const;

		/** Change the linear damping constant of this particle. */
		void SetDamping(const real damping);
		/** Get the linear damping constant of this particle. */
		real GetDamping() const;

		/** Set dead state of this particle. */
		void SetIsDead(bool isDead);
		/** Check if this particle is dead. */
		bool IsDead();

		/** Get current sum of accumulated forces. */
		const glm::vec3& GetForceAccum();
		/** Set the accumulated forces to zero. */
		void ClearAccumulator();

		/** Add a force to the force accumulator. */
		void AddForce(const glm::vec3 &force);

		/** Apply forces and update position, velocity and acceleration. */
		virtual void Integrate(real duration);

	protected:
		glm::vec3 m_position;
		glm::vec3 m_velocity;
		glm::vec3 m_acceleration;
		glm::vec3 m_forceAccum;
		real m_inverseMass;
		real m_damping;
		bool m_isDead;
	};
}