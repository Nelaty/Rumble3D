#pragma once
#include "R3D/Common/Common.h"
#include "IParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleGravity is a particle force generator, which
	 * applies a constant given force to particles.
	 */
	class R3D_DECLSPEC ParticleGravity : public IParticleForceGenerator
	{
	public:
		/**
		 * \brief ParticleGravity constructor
		 * \param gravity A constant force
		 */
		explicit ParticleGravity(const glm::vec3& gravity);
		~ParticleGravity();

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		*/
		void updateForce(Particle* particle) override;

		/** \brief Get the current gravity. */
		const glm::vec3& getGravity() const;
		/** \brief Set the current gravity. */
		void setGravity(const glm::vec3& gravity);

	protected:
		glm::vec3 m_gravity;
	};
}