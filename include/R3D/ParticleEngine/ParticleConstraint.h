#pragma once
#include "R3D/Common/Common.h"
#include "ParticleContactGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>



namespace r3
{
	class Particle;

	/**
	 * \brief Abstract class, which links a particle with a static
	 * position.
	 */
	class ParticleConstraint : public ParticleContactGenerator
	{
	public:
		virtual ~ParticleConstraint();

	protected:
		explicit ParticleConstraint();

		/**
		 * \brief Get the distance between the anchor point and the
		 * particle.
		 * \return The distance.
		 */
		real currentLength() const;

		glm::vec3 m_anchor;
		Particle* m_particle{};
	};
}
