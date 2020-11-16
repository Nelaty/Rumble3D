#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;

	/**
	 * Interface for particle force generators.
	 */
	class IParticleForceGenerator
	{
	public:
		virtual ~IParticleForceGenerator() = default;

		/**
		 * \brief Calculates and changes the force in the force accumulator
		 * of a particle.
		 * \param particle The particle, on which the force should be applied to.
		 * \param duration The duration for which the force acts
		 */
		virtual void updateForce(Particle* particle, real duration) = 0;

	protected:
		explicit IParticleForceGenerator() = default;
	};
}