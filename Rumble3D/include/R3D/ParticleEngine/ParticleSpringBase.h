#pragma once
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"

#include <glm/glm.hpp>

namespace r3
{
	class ParticleSpringBase : public IParticleForceGenerator
	{
	public:
		virtual ~ParticleSpringBase() = 0;

		/** \brief Set the spring resting length. */
		void setRestLength(real restLength);
		/** \brief Get the spring resting length. */
		real getRestLength() const;

		/** \brief Set the spring firmness. */
		void setSpringConstant(real constant);
		/** \brief Get the spring firmness. */
		real getSpringConstant() const;

	protected:
		explicit ParticleSpringBase() = default;
		explicit ParticleSpringBase(real springConstant,
									real restLength);

		/** \brief Check if a force can be calculated. */
		bool isMagnitudeValid(const glm::vec3& particle,
							  const glm::vec3& target,
							  glm::vec3& distance,
							  real& magnitude);

		/** \brief Calculate the spring force between two points. */
		glm::vec3 calculateForce(glm::vec3 distance,
								 real magnitude);

		real m_springConstant{0};
		real m_restLength{0};
	};
}