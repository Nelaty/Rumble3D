#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/ParticleSpringBase.h"

#include <glm/glm.hpp>

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleAnchoredSpring is a particle generator, which
	 * simulates a spring, which is anchored to a specific point.
	 * \details The specified point itself can move, but it will not be 
	 * affected by this force generator.
	 */
	class R3D_DECLSPEC ParticleAnchoredSpring : public ParticleSpringBase
	{
	public:
		/**
		 * \brief ParticleAnchoredSpring constructor
		 * \param anchor An immovable end of the spring 
		 * \param springConstant Defines the hardness of the spring
		 * \param restLength The length at which no forces are applied
		 */
		explicit ParticleAnchoredSpring(glm::vec3* anchor, real springConstant, real restLength);
		~ParticleAnchoredSpring() = default;

		/**
		* \brief Calculates and changes the force in the force accumulator
		* of a particle.
		* \param particle The particle, on which the force should be applied to.
		* \param duration The duration for which the force acts
		*/
		void updateForce(Particle* particle) override;
	
	protected:
		glm::vec3* m_anchor;
	};
}