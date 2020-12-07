#pragma once
#include "R3D/Water/SPHEngine/Kernel/ISPHKernel.h"

namespace r3
{
    class ForceKernelCpuSerial : public ISPHKernel
    {
    public:
        explicit ForceKernelCpuSerial() = default;
        ~ForceKernelCpuSerial() = default;

        void execute(const SPHContext_Ptr &context) override;
    };
}


