#pragma once
#include "R3D/ParticleEngine/ParticleSpringBase.h"

namespace r3
{
	/**
	 * The ParticleBidirectionalSpring acts like two ParticleSprings, which 
	 * connects two particles, so that both particles are affected.
	 */
	class R3D_DECLSPEC ParticleBidirectionalSpring : public ParticleSpringBase
	{
	public:
	    /**
	     * Construct a zero initialized ParticleBidirectionalSpring.
	     */
	    explicit ParticleBidirectionalSpring() = default;
		/**
		* \brief ParticleSpring constructor.
		* \param other The other particle, which will be pulled towards the
		* particle in updateForce.
		* \param springConstant The hardness of the spring.
		* \param restLength The length at which no forces will be applied.
		*/
		explicit ParticleBidirectionalSpring(Particle* other, 
											 real springConstant, 
											 real restLength);
		~ParticleBidirectionalSpring() = default;

        /** \brief Set the other particle of this spring. */
        void setOther(Particle* other);
        /** \brief Get the other particle of this spring. */
        Particle* getOther();

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		* \param duration The duration for which the force acts.
		*/
		void updateForce(Particle* particle) override;

	private:
		Particle* m_other{nullptr};
	};
}