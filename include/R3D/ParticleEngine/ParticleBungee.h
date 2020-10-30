#pragma once
#include "R3D/Common/Common.h"
#include "ParticleSpringBase.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleBungee is a particle force generator, which
	 * simulates a bungee cord and connects two particles.
	 */
	class R3D_DECLSPEC ParticleBungee : public ParticleSpringBase
	{
	public:
		/**
		 * \brief ParticleBungee constructor.
		 * \param other The other particle, connected to this bungee cord.
		 * \param springConstant Defines the hardness of the bungee cord.
		 * \param restLength The threshold at which forces will be applied.
		 */
		explicit ParticleBungee(Particle* other, real springConstant, real restLength);
		~ParticleBungee() = default;

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		* \param duration The duration for which the force acts
		*/
		void updateForce(Particle* particle, real duration) override;

	protected:
		Particle* m_other;
	};
}

