//
// Created by root on 26.09.20.
//

#pragma once

#include <glm/glm.hpp>

namespace r3
{
    class SmoothingKernel
    {
    public:
        static glm::vec3 smoothVec3(const glm::vec3& vector, float smoothingLength);
        static float smoothScalar(const glm::vec3& vector, float smoothingLength);
    };
}




