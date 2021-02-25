#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/ParticleContactGenerator.h"

#include <glm/glm.hpp>

namespace r3
{
	class Particle;

	/**
	 * \brief Abstract class, which links a particle with a static
	 * position.
	 */
	class R3D_DECLSPEC ParticleConstraint : public ParticleContactGenerator
	{
	public:
		virtual ~ParticleConstraint() = default;

	protected:
		explicit ParticleConstraint() = default;

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
