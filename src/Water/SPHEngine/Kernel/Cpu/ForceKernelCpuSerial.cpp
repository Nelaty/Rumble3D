#include "R3D/Water/SPHEngine/Kernel/Cpu/ForceKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Entity/SPHSystem.h"
#include "R3D/Water/SPHEngine/Entity/SPHParticleDefinition.h"
#include "R3D/Water/SPHEngine/Entity/SPHParams.h"

#include "R3D/Water/SPHEngine/Kernel/Cpu/SmoothingKernel.h"

namespace r3
{
    void ForceKernelCpuSerial::execute(const SPHContext_Ptr& context)
    {
        auto& particles = context->m_system->getParticles();
        const auto& defs = context->m_system->getParticleDefinitions();
        const auto& params = context->m_params;

        for(auto& it : particles)
        {
            glm::vec3 force(0.0);
            for(const auto& other : particles)
            {
                const auto& massOther = defs[it.m_definition]->m_mass;
                force += float(glm::pow(massOther, 2))
                        * float(((it.m_pressure / glm::pow(it.m_density, 2)) + (other.m_pressure / glm::pow(other.m_density, 2))))
                        * SmoothingKernel::smoothVec3(it.m_position - other.m_position, params->m_smoothingLength);
            }
            it.m_forces -= force;
        }
    }
}