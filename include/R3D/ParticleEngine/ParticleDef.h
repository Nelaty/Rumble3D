#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	/**
	 * \brief Bundles construction information of a particle.
	 */
	struct ParticleDef
	{
		glm::vec3 m_position{0};
		glm::vec3 m_velocity{0};
		glm::vec3 m_acceleration{0};

		glm::vec3 m_forceAccumulator{0};
		real m_damping{static_cast<real>(0.999)};

		void setMass(real mass);
		void setInfiniteMass();
		real m_inverseMass{0};

		bool m_isDead{false};
	};
}
