#pragma once
#include "R3D/ParticleEngine/IParticleForceGenerator.h"

namespace r3
{
	/**
	 * The ParticleBidirectionalSpring acts like two ParticleSprings, which 
	 * connects two particles, so that both particles are affected.
	 */
	class ParticleBidirectionalSpring : public IParticleForceGenerator
	{
	public:
		/**
		* \brief ParticleSpring constructor.
		* \param other The other particle, which will be pulled towards the
		* particle in updateForce.
		* \param springConstant The hardness of the spring.
		* \param restLength The length at which no forces will be applied.
		*/
		ParticleBidirectionalSpring(Particle* other, 
									real springConstant, 
									real restLength);
		~ParticleBidirectionalSpring();

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		*/
		void updateForce(Particle* particle) override;

	private:
		Particle* m_other;

		real m_springConstant;
		real m_restLength;
	};
}