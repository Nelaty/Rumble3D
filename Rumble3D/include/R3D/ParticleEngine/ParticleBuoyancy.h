#pragma once
#include "R3D/Common/Common.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleBuoyancy is a particle force generator, which can
	 * simulate buoyancy.
	 * \details It can only simulate buoyancy in an axis aligned half space
	 * perpendicular to the y-axis.
	 */
	class R3D_DECLSPEC ParticleBuoyancy : public IParticleForceGenerator
	{
	public:
		/**
		 * \brief ParticleBuoyancy constructor.
		 * \param maxDepth Depth in [m] at which the body is completely
		 * submerged.
		 * \param volume Volume of the body in [m^3].
		 * \param liquidHeight Height of the liquid in [m].
		 * \param liquidDensity Density of the volume in [kg/m^3].
		 */
		explicit ParticleBuoyancy(real maxDepth,
								  real volume, 
								  real liquidHeight, 
								  real liquidDensity = real(1000),
								  real gravity = real(9.81));
		~ParticleBuoyancy();

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		* \param duration The duration for which the force acts.
		*/
		void updateForce(Particle* particle, real duration) override;

		/** \brief Get the current at which the body is completely submerged. */
		real getMaxDepth() const;
		/** \brief Set the current at which the body is completely submerged. */
		void setMaxDepth(real depth);

		/** \brief Get the volume of the body. */
		real getVolume() const;
		/** \brief Set the volume of the body. */
		void setVolume(real depth);

		/** \brief Get the current liquid height. */
		real getLiquidHeight() const;
		/** \brief Set the current liquid height. */
		void setLiquidHeight(real height);

		/** \brief Get the current liquid density. */
		real getLiquidDensity() const;
		/** \brief Set the current liquid density. */
		void setLiquidDensity(real density);

		/** \brief Get the up-force of this generator. */
		real getGravity() const;
		/** \brief Set the up-force of this generator. */
		void setGravity(real gravity);

	protected:
		real m_maxDepth;
		real m_volume;
		real m_liquidHeight;
		real m_liquidDensity;

		real m_gravity;
	};
}