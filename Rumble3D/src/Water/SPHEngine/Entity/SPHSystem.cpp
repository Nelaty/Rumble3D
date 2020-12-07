#include "R3D/Water/SPHEngine/Entity/SPHSystem.h"

#include <algorithm>

namespace r3
{

    const std::vector<SPHParticle>& SPHSystem::getParticles() const
    {
        return m_particles;
    }

    void SPHSystem::clear()
    {
        m_particles.clear();
        m_particleDefinitions.clear();
    }

    SPHParticle& SPHSystem::addParticle(int particleDefinitionId)
    {
        assert(particleDefinitionId >= 0 && particleDefinitionId < m_particleDefinitions.size());

        SPHParticle particle;
        particle.m_definition = particleDefinitionId;
        return m_particles.emplace_back(particle);
    }

    int SPHSystem::getParticleDefinitionId(const SPHSystem::ParticleDefinition_Ptr& definition) const
    {
        for(auto i = 0; i < m_particleDefinitions.size(); ++i)
        {
            if(m_particleDefinitions[i] == definition)
            {
                return i;
            }
        }
        return -1;
    }

    int SPHSystem::addParticleDefinition(const SPHSystem::ParticleDefinition_Ptr& definition)
    {
        for(auto i = 0; i < m_particleDefinitions.size(); ++i)
        {
            if(m_particleDefinitions[i] == definition)
            {
                return i;
            }
        }
        m_particleDefinitions.emplace_back(definition);
        return m_particleDefinitions.size() - 1;
    }

    std::vector<SPHParticle>& SPHSystem::getParticles()
    {
        return m_particles;
    }

    const std::vector<SPHSystem::ParticleDefinition_Ptr>& SPHSystem::getParticleDefinitions() const
    {
        return m_particleDefinitions;
    }
}