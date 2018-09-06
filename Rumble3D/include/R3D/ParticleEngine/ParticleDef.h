#pragma once
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	struct ParticleDef
	{
		glm::vec3 m_position{0.0f};
		glm::vec3 m_velocity{0.0f};
		glm::vec3 m_acceleration{0.0f};

		glm::vec3 m_forceAccumulator{0.0f};
		real m_damping{0.999f};

		void setMass(real mass);
		void setInfiniteMass();
		real m_inverseMass{0.0f};

		bool m_isDead{false};
	};
}
