#pragma once
#include <memory>

#include <glm/glm.hpp>

namespace r3
{
    class SPHSystem;
    struct SPHParams;

    class SPHContext
    {
    public:
        explicit SPHContext();
        virtual ~SPHContext() = default;

        std::shared_ptr<SPHSystem> m_system;
        std::shared_ptr<SPHParams> m_params;

        glm::vec3 m_globalForce{0.0};
    };
}



