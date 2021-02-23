#pragma once
#include <R3D/Common/Common.h>
#include <R3D/Water/SPHEngine/Entity/SPHParticle.h>

#include <memory>
#include <map>
#include <vector>

namespace r3
{
    class SPHParticleDefinition;

    class R3D_DECLSPEC SPHSystem
    {
    public:
        using ParticleDefinition_Ptr = std::shared_ptr<SPHParticleDefinition>;

        explicit SPHSystem() = default;
        ~SPHSystem() = default;

        SPHParticle& addParticle(int particleDefinitionId);
        std::vector<SPHParticle>& getParticles();
        const std::vector<SPHParticle>& getParticles() const;

        int getParticleDefinitionId(const ParticleDefinition_Ptr& definition) const;
        int addParticleDefinition(const ParticleDefinition_Ptr& definition);
        const std::vector<ParticleDefinition_Ptr>& getParticleDefinitions() const;

        void clear();

    private:
        std::vector<SPHParticle> m_particles;
        std::vector<ParticleDefinition_Ptr> m_particleDefinitions;
    };
}