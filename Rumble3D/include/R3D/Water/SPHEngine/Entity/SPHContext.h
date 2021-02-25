#pragma once
#include "R3D/Common/Common.h"

#include <glm/glm.hpp>
#include <memory>

namespace r3
{
    class SPHSystem;
    struct SPHParams;

    class R3D_DECLSPEC SPHContext
    {
    public:
        explicit SPHContext();
        virtual ~SPHContext() = default;

        std::shared_ptr<SPHSystem> m_system;
        std::shared_ptr<SPHParams> m_params;

        glm::vec3 m_globalForce{0.0};
    };
}



