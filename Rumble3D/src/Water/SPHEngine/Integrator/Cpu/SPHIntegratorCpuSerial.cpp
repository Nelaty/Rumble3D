#include "R3D/Water/SPHEngine/Integrator/Cpu/SPHIntegratorCpuSerial.h"

#include "R3D/Water/SPHEngine/Entity/SPHSystem.h"
#include "R3D/Water/SPHEngine/Entity/SPHParticleDefinition.h"
#include "R3D/Water/SPHEngine/Entity/SPHParams.h"

namespace r3
{
    void SPHIntegratorCpuSerial::integrate(const SPHContext_Ptr& context, float timeDelta)
    {
        auto& particles = context->m_system->getParticles();
        const auto& definitions = context->m_system->getParticleDefinitions();
        const auto& params = context->m_params;

        for(auto& it : particles)
        {
            float mass = definitions[it.m_definition]->m_mass;
            glm::vec3 acceleration = (context->m_globalForce + it.m_forces) / mass;

            it.m_velocity += timeDelta * acceleration;
            it.m_velocity *= glm::pow(params->m_damping, timeDelta);

            it.m_position += timeDelta * it.m_velocity;

            it.m_forces = glm::vec3(0.0);
        }
    }
}