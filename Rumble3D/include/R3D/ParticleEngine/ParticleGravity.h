#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"

#include <glm/glm.hpp>

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleGravity is a particle force generator, which
	 * applies a constant given force to particles.
	 */
	class R3D_EXPORT ParticleGravity : public IParticleForceGenerator
	{
	public:
		/**
		 * \brief ParticleGravity constructor
		 * \param gravity A constant force
		 */
		explicit ParticleGravity(real uniform);
		explicit ParticleGravity(real x, real y, real z);
		explicit ParticleGravity(const glm::vec3& gravity = glm::vec3(0.0, -9.81, 0.0));
		~ParticleGravity() = default;

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		* \param duration The duration for which the force acts.
		*/
		void updateForce(Particle* particle) override;

		/** \brief Get the current gravity. */
		const glm::vec3& getGravity() const;
		/** \brief Set the current gravity. */
		void setGravity(const glm::vec3& gravity);
        /** \brief Set the current gravity. */
		void setGravity(real x, real y, real z);
        /** \brief Set the current gravity. */
		void setGravity(real uniform);

	protected:
		glm::vec3 m_gravity;
	};
}