#pragma once
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/IParticleForceGenerator.h"

#include <glm/glm.hpp>

namespace r3
{
    /**
     * \brief A base class for spring like force generators, which can
     * calculate forces between two points according to Hooke's Law.
     * @f$ F_s = -kx @f$
     */
	class R3D_EXPORT ParticleSpringBase : public IParticleForceGenerator
	{
	public:
		virtual ~ParticleSpringBase() = default;

		/** \brief Set the spring resting length. */
		void setRestLength(real restLength);
		/** \brief Get the spring resting length. */
		real getRestLength() const;

		/** \brief Set the spring firmness. */
		void setSpringConstant(real constant);
		/** \brief Get the spring firmness. */
		real getSpringConstant() const;

        /** \brief Check if a force can be calculated.
         * \param target First position (distance will point towards this position)
         * \param source Second position
         * \param [out] distance Distance vector between the given positions
         * \param [out] magnitude Magnitude of the distance*/
        bool isMagnitudeValid(const glm::vec3& target,
                              const glm::vec3& source,
                              glm::vec3& distance,
                              real& magnitude) const;

	protected:
		explicit ParticleSpringBase() = default;
		explicit ParticleSpringBase(real springConstant,
									real restLength);

        /** \brief Calculate the spring force between two points.
         * \param distance Distance vector between two points. Undefined behavior for zero vector.
         * \param magnitude The length of the distance vector. */
        glm::vec3 calculateForce(glm::vec3 distance,
                                 real magnitude) const;

		real m_springConstant{0};
		real m_restLength{0};
	};
}