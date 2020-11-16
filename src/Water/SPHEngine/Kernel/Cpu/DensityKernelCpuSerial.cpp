#include "R3D/Water/SPHEngine/Kernel/Cpu/DensityKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/SmoothingKernel.h"
#include "R3D/Water/SPHEngine/Entity/SPHSystem.h"
#include "R3D/Water/SPHEngine/Entity/SPHParticleDefinition.h"
#include "R3D/Water/SPHEngine/Entity/SPHParams.h"

namespace r3
{
    void DensityKernelCpuSerial::execute(const SPHContext_Ptr& context)
    {
        auto& particles = context->m_system->getParticles();
        const auto& defs = context->m_system->getParticleDefinitions();
        const auto& params = context->m_params;

        for(auto& p : particles)
        {
            p.m_density = 0.0f;
            for(const auto& other : particles)
            {
                p.m_density +=
                        defs[other.m_definition]->m_mass
                        * SmoothingKernel::smoothScalar(p.m_position - other.m_position, params->m_smoothingLength);
            }
        }
    }
}