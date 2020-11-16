//
// Created by root on 26.09.20.
//

#pragma once

#include <glm/glm.hpp>

namespace r3
{
    struct SPHParticle
    {
        glm::vec3 m_position{0.0};
        glm::vec3 m_velocity{0.0};
        glm::vec3 m_forces{0.0};

        float m_density{0.0};
        float m_pressure{0.0};

        int m_definition{-1};
    };
}




