#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include "R3D/ParticleEngine/ParticleDef.h"

#include <glm/glm.hpp>

namespace r3 
{
	/**
	 * A particle represents a single point in space with physical
	 * properties. A particle has no orientation and therefor can't
	 * be rotated.
	 */
	class R3D_DECLSPEC Particle 
	{
	public:
		explicit Particle();
		explicit Particle(const ParticleDef& definition);
		virtual ~Particle();

		/**
		 * Initialize this particle with a given definition.
		 * Automatically called from constructors.
		 */
		void init(const ParticleDef& definition);

		/**
		 * Change the mass of this particle to the given given value. 
		 * Implicitly changes inverse mass.
		 */
		void setMass(real mass);
		/** Get the current mass of this particle. */
		real getMass() const;
		/** 
		 * Change the inverse mass of this particle to the given value.
		 * Implicitly changes mass.
		 * \param inverseMass A value of 0 is equivalent to infinite mass.
		 */
		void setInverseMass(real inverseMass);
		/**
		 * Get the current inverse mass of this particle
		 * If particle has infinite mass, inverse mass will be 0.
		 */
		real getInverseMass() const;
		/**
		 * Check if this particle has infinite mass.
		 * \return True if mass is infinite.
		 */
		bool hasFiniteMass() const;

		/** Change particle position to given vector. */
		void setPosition(const glm::vec3 &position);
		/** Change particle position to given coordinates. */
		void setPosition(real x, real y, real z);
		/** Get the current position of this particle. */
		const glm::vec3& getPosition() const;

		/** Change the current velocity of this particle to the given velocity. */
		void setVelocity(const glm::vec3 &velocity);
		/** Change the current velocity of this particle to the given velocity. */
		void setVelocity(real x, real y, real z);
		/** Get the current velocity of this particle. */
		const glm::vec3& getVelocity() const;

		/** Change the current acceleration of this particle to the given acceleration. */
		void setAcceleration(const glm::vec3 &acceleration);
		/** Change the current acceleration of this particle to the given acceleration. */
		void setAcceleration(real x, real y, real z);
		/** Get the current acceleration of this particle. */
		const glm::vec3& getAcceleration() const;

		/** Change the linear damping constant of this particle. */
		void setDamping(real damping);
		/** Get the linear damping constant of this particle. */
		real getDamping() const;

		/** Set dead state of this particle. */
		void setIsDead(bool isDead);
		/** Check if this particle is dead. */
		bool isDead() const;

		/** Get current sum of accumulated forces. */
		const glm::vec3& getForceAccumulator() const;
		/** Set the accumulated forces to zero. */
		void clearAccumulator();

		/** Add a force to the force accumulator. */
		void addForce(const glm::vec3 &force);

		/** Apply forces and update position, velocity and acceleration. */
		virtual void integrate(real duration);

	protected:
		glm::vec3 m_position;
		glm::vec3 m_velocity;
		glm::vec3 m_acceleration;

		glm::vec3 m_forceAccumulator;
		real m_damping;

		real m_inverseMass;
		
		bool m_isDead;
	};
}