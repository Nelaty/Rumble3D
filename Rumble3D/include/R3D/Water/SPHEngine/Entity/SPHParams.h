#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
    struct R3D_DECLSPEC SPHParams
    {
        float m_smoothingLength{s_defaultSmoothingLength};
        float m_stiffnessParameter{s_defaultStiffnessParameter};
        float m_gamma{s_defaultGamma};
        float m_damping{s_defaultDamping};

        /** Default values */
        static constexpr float s_defaultSmoothingLength = 1.0f;
        static constexpr float s_defaultStiffnessParameter = 1.0f;
        static constexpr float s_defaultGamma = 1.0f;
        static constexpr float s_defaultDamping = 0.999f;
    };
}