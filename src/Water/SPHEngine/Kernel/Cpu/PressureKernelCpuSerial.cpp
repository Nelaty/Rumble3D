#include "R3D/Water/SPHEngine/Kernel/Cpu/PressureKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Entity/SPHSystem.h"
#include "R3D/Water/SPHEngine/Entity/SPHParticleDefinition.h"
#include "R3D/Water/SPHEngine/Entity/SPHParams.h"

namespace r3
{
    void PressureKernelCpuSerial::execute(const SPHContext_Ptr& context)
    {
        auto& particles = context->m_system->getParticles();
        const auto& defs = context->m_system->getParticleDefinitions();
        const auto& params = context->m_params;

        for(auto& p : particles)
        {
            const auto& def = defs[p.m_definition];
            p.m_pressure = params->m_stiffnessParameter * def->m_referenceDensity / params->m_gamma;
            p.m_pressure *= glm::pow(p.m_density / def->m_referenceDensity, params->m_gamma) - 1.0f;
        }
    }
}