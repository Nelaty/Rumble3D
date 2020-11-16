#pragma once

#include "R3D/Water/SPHEngine/Kernel/ISPHKernel.h"

namespace r3
{
    class DensityKernelCpuSerial : public ISPHKernel
    {
    public:
        explicit DensityKernelCpuSerial() = default;
        ~DensityKernelCpuSerial() = default;

        void execute(const SPHContext_Ptr&context) override;
    };
}




