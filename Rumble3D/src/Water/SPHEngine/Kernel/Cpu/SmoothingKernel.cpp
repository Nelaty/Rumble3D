#include <glm/ext/scalar_constants.hpp>
#include "R3D/Water/SPHEngine/Kernel/Cpu/SmoothingKernel.h"


namespace r3
{
    namespace
    {
        float kernelValue(float r, float h)
        {
            if(r <= h)
            {
                float r_h = r / h;
                return 1.0f - (3.0f/2.0f) * r_h * r_h + (3.0f/4.0f) * glm::pow(r_h, 3);
            }
            else if(r <= 2.0f * h)
            {
                return (1.0f/4.0f) * glm::pow(2.0f - r/h, 3);
            }
            else
            {
                return 0;
            }
        }
    }


    glm::vec3 SmoothingKernel::smoothVec3(const glm::vec3& vector, float smoothingLength)
    {
        float constant = 1.0f / (glm::pi<float>() * glm::pow(smoothingLength, 3));

        glm::vec3 result(
                glm::sign(vector.x) * kernelValue(abs(vector.x), smoothingLength),
                glm::sign(vector.y) * kernelValue(abs(vector.y), smoothingLength),
                glm::sign(vector.z) * kernelValue(abs(vector.z), smoothingLength)
        );

        return result * constant;
    }

    float SmoothingKernel::smoothScalar(const glm::vec3& vector, float smoothingLength)
    {
        float constant = 1.0f / (glm::pi<float>() * glm::pow(smoothingLength, 3));

        return constant * kernelValue(glm::length(vector), smoothingLength);
    }
}