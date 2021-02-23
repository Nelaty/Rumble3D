#pragma once
#include <R3D/Common/Common.h>

#include <glm/glm.hpp>

namespace r3
{
    class R3D_DECLSPEC SmoothingKernel
    {
    public:
        static glm::vec3 smoothVec3(const glm::vec3& vector, float smoothingLength);
        static float smoothScalar(const glm::vec3& vector, float smoothingLength);
    };
}




