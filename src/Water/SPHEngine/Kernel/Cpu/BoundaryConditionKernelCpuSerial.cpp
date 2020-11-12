#include "R3D/Water/SPHEngine/Kernel/Cpu/BoundaryConditionKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Entity/SPHSystem.h"
#include "R3D/Water/SPHEngine/Entity/SPHParticleDefinition.h"
#include "R3D/Water/SPHEngine/Entity/SPHParams.h"

namespace r3
{

    BoundaryConditionKernelCpuSerial::BoundaryConditionKernelCpuSerial(const glm::vec3& offset,
                                                                       const glm::vec3& halfSizes)
                                                                       : m_offset(offset),
                                                                       m_halfSizes(halfSizes)
    {
    }

    void BoundaryConditionKernelCpuSerial::execute(const ISPHKernel::SPHContext_Ptr& context)
    {
        auto& particles = context->m_system->getParticles();
        const auto& defs = context->m_system->getParticleDefinitions();

        for(auto& it : particles)
        {
            float radius = defs[it.m_definition]->m_radius;
            applyBoundaryCondition(it, radius);
        }
    }



    const glm::vec3& BoundaryConditionKernelCpuSerial::getOffset() const
    {
        return m_offset;
    }

    void BoundaryConditionKernelCpuSerial::setOffset(const glm::vec3& offset)
    {
        m_offset = offset;
    }

    const glm::vec3& BoundaryConditionKernelCpuSerial::getHalfSizes() const
    {
        return m_halfSizes;
    }

    void BoundaryConditionKernelCpuSerial::setHalfSizes(const glm::vec3& halfSizes)
    {
        m_halfSizes = halfSizes;
    }

    void BoundaryConditionKernelCpuSerial::applyBoundaryCondition(SPHParticle& particle, float radius)
    {
        glm::vec3 force{0.0f};
        force += applyBoundaryConditionAxis(particle, radius, glm::vec3(0.0, 1.0, 0.0));
        force += applyBoundaryConditionAxis(particle, radius, glm::vec3(0.0, -1.0, 0.0));
        force += applyBoundaryConditionAxis(particle, radius, glm::vec3(1.0, 0.0, 0.0));
        force += applyBoundaryConditionAxis(particle, radius, glm::vec3(-1.0, 0.0, 0.0));
        force += applyBoundaryConditionAxis(particle, radius, glm::vec3(0.0, 0.0, 1.0));
        force += applyBoundaryConditionAxis(particle, radius, glm::vec3(0.0, 0.0, -1.0));
        particle.m_forces += force;
    }

    glm::vec3
    BoundaryConditionKernelCpuSerial::applyBoundaryConditionAxis(SPHParticle& particle, float radius, glm::vec3 axis)
    {
        glm::vec3 distVec = particle.m_position - m_offset + m_halfSizes;
        glm::vec3 shortestDistVec = glm::dot(axis, distVec) * axis;

        float distance = glm::length(shortestDistVec);
        if(distance > m_r0) return glm::vec3(0.0);

        float div = m_r0 / distance;
        return axis * float(m_D * float(glm::pow(div, m_n1) - glm::pow(div, m_n2)) * 1.0f / glm::pow(distance, 2.0));
    }
}