#pragma once
#include "R3D/Common/Common.h"

#include <glm/glm.hpp>

namespace r3
{
    struct R3D_DECLSPEC SPHParticle
    {
        glm::vec3 m_position{0.0};
        glm::vec3 m_velocity{0.0};
        glm::vec3 m_forces{0.0};

        float m_density{0.0};
        float m_pressure{0.0};

        int m_definition{-1};
    };
}




