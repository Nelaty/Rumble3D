#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Water/SPHEngine/Entity/SPHParticle.h"
#include "R3D/Water/SPHEngine/Kernel/ISPHKernel.h"

namespace r3
{
    // Makes usage of Lennard-Jones potential to restrain SPHParticles to a
    // boundary box
    class R3D_DECLSPEC BoundaryConditionKernelCpuSerial : public ISPHKernel
    {
    public:
    public:
        explicit BoundaryConditionKernelCpuSerial(const glm::vec3& offset = glm::vec3(0.0),
                                      const glm::vec3& halfSizes = glm::vec3(1.0));
        ~BoundaryConditionKernelCpuSerial() = default;

        void execute(const SPHContext_Ptr &context) override;

        const glm::vec3& getOffset() const;
        void setOffset(const glm::vec3& offset);

        const glm::vec3& getHalfSizes() const;
        void setHalfSizes(const glm::vec3& halfSizes);

        // TODO: replace with square of largest velocity
        static constexpr float m_D{500};
        static constexpr float m_r0{0.1};
        static constexpr float m_n1{12.0};
        static constexpr float m_n2{4.0};

    private:
        void applyBoundaryCondition(r3::SPHParticle& particle, float radius);
        glm::vec3 applyBoundaryConditionAxis(r3::SPHParticle& particle, float radius, glm::vec3 axis);

        glm::vec3 m_offset;
        glm::vec3 m_halfSizes;
    };
}




