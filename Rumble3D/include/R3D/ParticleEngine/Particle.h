#pragma once
#include <R3D/Common/Common.h>
#include <R3D/Common/Precision.h>

#include <R3D/ParticleEngine/ParticleDef.h>

#include <glm/glm.hpp>

namespace r3 
{
	/**
	 * \brief A Particle represents a single point in space with physical
	 * properties. A particle has no orientation and therefor can't
	 * be rotated.
	 */
	class R3D_DECLSPEC Particle
	{
	public:
		/**
		 * \brief Particle default constructor.
		 */
		explicit Particle();
		/**
		 * \brief Particle constructor
		 * \param definition The properties of this particle.
		 */
		explicit Particle(const ParticleDef& definition);
		virtual ~Particle() = default;

		bool operator==(const Particle& rhs) const = default;

		/**
		 * \brief Initialize this particle.
		 * \param definition The properties of this particle
		 */
		void init(const ParticleDef& definition);

		/**
		 * \brief Set the mass of this particle.
		 * \param mass The new mass.
		 * \details Implicitly changes inverse mass.
		 */
		void setMass(real mass);
		/** 
		 * \brief Get the current mass of this particle.
		 * \return The current mass.
		 */
		real getMass() const;
		/** 
		 * \brief Change the inverse mass of this particle to the given value.
		 * \param inverseMass A value of 0 is equivalent to infinite mass.
		 * \details Implicitly changes mass.
		 */
		void setInverseMass(real inverseMass);
		/**
		 * \brief Get the current inverse mass of this particle
		 * \return The inverse mass. If particle has infinite mass, 
		 * the inverse mass will be 0.
		 */
		real getInverseMass() const;
		/**
		 * \brief Check if this particle has infinite mass.
		 * \return True if mass is infinite, false otherwise.
		 */
		bool hasFiniteMass() const;

		/** 
		 * \brief Change the particle's position. 
		 * \param position The new position.
		 */
		void setPosition(const glm::vec3 &position);
		/** 
		 * \brief Change the particle's position.
		 * \param x The new x coordinate
		 * \param y The new y coordinate
		 * \param z The new z coordinate
		 */
		void setPosition(real x, real y, real z);
		/** 
		 * \brief Get the particle's position.
		 * \return The current position.
		 */
		const glm::vec3& getPosition() const;

		/** 
		 * \brief Change the particle's velocity.
		 * \param velocity The new velocity
		 */
		void setVelocity(const glm::vec3& velocity);
		/** 
		 * \brief Change the particle's velocity.
		 * \param x The x component of the new velocity
		 * \param y The y component of the new velocity
		 * \param z The z component of the new velocity
		 */
		void setVelocity(real x, real y, real z);
		/** 
		 * \brief Get the particle's velocity.
		 * \return The current velocity 
		 */
		const glm::vec3& getVelocity() const;

		/** 
		 * \brief Change the particle's acceleration
		 * \param acceleration The new acceleration
		 */
		void setAcceleration(const glm::vec3& acceleration);
		/**
		 * \brief Change the particle's acceleration
		 * \param x The x component of the new acceleration
		 * \param y The y component of the new acceleration
		 * \param z The z component of the new acceleration
		 */
		void setAcceleration(real x, real y, real z);
		/** 
		 * \brief Get the particle's acceleration
		 * \return The current acceleration
		 */
		const glm::vec3& getAcceleration() const;

		/** 
		 * \brief Change the particle's linear damping.
		 * \param damping The new damping constant
		 */
		void setDamping(real damping);
		/**
		 * \brief Get the particle's linear damping.
		 * \return The current damping constant.
		 */
		real getDamping() const;

		/**
		 * \brief Set the particle's dead flag.
		 * \param isDead Death flag
		 */
		void setIsDead(bool isDead);
		/** 
		 * \brief Check if the particle is dead.
		 * \return True if the particle is dead, false otherwise.
		 */
		bool isDead() const;

		/** 
		 * \brief Get the sum of forces, accumulated since the last update
		 * \return Sum of accumulated forces
		 */
		const glm::vec3& getForceAccumulator() const;
		/** 
		 * \brief Reset the force accumulator to zero
		 */
		void clearAccumulator();

		/** 
		 * \brief Add a force to the force accumulator. 
		 * \param force The force to be added
		 */
		void addForce(const glm::vec3& force);

		/**
		 * \brief Reset position, velocity, acceleration, force accumulator
		 * and dead status.
		 */
		void reset(const glm::vec3& position = glm::vec3(0.0));

		/** 
		 * \brief Integrate changes made to the particle.
		 * \details Apply forces and update position, velocity and acceleration. 
		 */
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