#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Water/SPHEngine/Kernel/ISPHKernel.h"

namespace r3
{
    class R3D_DECLSPEC ForceKernelCpuSerial : public ISPHKernel
    {
    public:
        explicit ForceKernelCpuSerial() = default;
        ~ForceKernelCpuSerial() = default;

        void execute(const SPHContext_Ptr &context) override;
    };
}
