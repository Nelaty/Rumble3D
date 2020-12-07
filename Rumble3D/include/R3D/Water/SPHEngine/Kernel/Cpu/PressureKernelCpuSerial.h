#pragma once
#include "R3D/Water/SPHEngine/Kernel/ISPHKernel.h"

namespace r3
{
    class PressureKernelCpuSerial : public ISPHKernel
    {
    public:
        explicit PressureKernelCpuSerial() = default;
        ~PressureKernelCpuSerial() = default;

        void execute(const SPHContext_Ptr &context) override;
    };
}




