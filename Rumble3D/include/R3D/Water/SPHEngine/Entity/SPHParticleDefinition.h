#pragma once
#include <R3D/Common/Common.h>

namespace r3
{
    struct R3D_DECLSPEC SPHParticleDefinition
    {
        float m_referenceDensity{1.0};
        float m_mass{1.0};
        float m_radius{1.0};
        //float m_squaredMass{1.0};
    };
}




