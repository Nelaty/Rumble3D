#pragma once

#include "R3D/Water/SPHEngine/Integrator/ISPHIntegrator.h"

namespace r3
{
    class SPHIntegratorCpuSerial : public ISPHIntegrator
    {
    public:
        explicit SPHIntegratorCpuSerial() = default;
        ~SPHIntegratorCpuSerial() = default;

        void integrate(const SPHContext_Ptr& context, float timeDelta) override;
    };
}



