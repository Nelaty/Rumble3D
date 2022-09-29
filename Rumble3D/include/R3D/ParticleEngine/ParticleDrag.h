#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"

#include <glm/gtc/constants.hpp>

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleDrag is a particle force generator, which 
	 * simulates the effect of drag forces.
	 */
	class R3D_EXPORT ParticleDrag : public IParticleForceGenerator
	{
	public:
		/**
		* \brief ParticleDrag constructor
		* \param crossSectionalArea
		* \param dragCoefficient 
		* \param mediumDensity Density of the surrounding medium in [kg/m^3]
		* 
		* \details
		* Cross sectional area of a smooth sphere = 2 * r * pi
		* Drag coefficient of a smooth sphere = 0.47, RE = 10^5 (RE = Reynolds Number)
		* Density of air at 15�C = 1.225
		*/
		explicit ParticleDrag(real crossSectionalArea = glm::two_pi<real>(),
							  real dragCoefficient = real(0.47),
							  real mediumDensity = real(1.225));
		~ParticleDrag() = default;

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		* \param duration The duration for which the force acts
		*/
		void updateForce(Particle* particle) override;

	protected:
		real m_crossSectionalArea;
		real m_dragCoefficient;
		real m_mediumDensity;
	};
}