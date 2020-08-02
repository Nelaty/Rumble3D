#pragma once
#include "IParticleForceGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleSpring is a particle force generator, which
	 * simulates a spring between two particles.
	 * \details The spring force will not be applied to the particle,
	 * which is assigned to this generator.
	 */
	class R3D_DECLSPEC ParticleSpring : public IParticleForceGenerator
	{	
	public:
		/**
		 * \brief ParticleSpring constructor.
		 * \param other The reference position. Will not be influenced
		 * by the spring.
		 * \param springConstant The hardness of the spring.
		 * \param restLength The length at which no forces will be applied.
		 */
		ParticleSpring(Particle* other, real springConstant, real restLength);
		~ParticleSpring();

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		* \param duration The duration for which the force acts.
		*/
		void updateForce(Particle* particle, real duration) override;

	protected:
		real m_springConstant;
		real m_restLength;
		
		Particle* m_other;
	};
}