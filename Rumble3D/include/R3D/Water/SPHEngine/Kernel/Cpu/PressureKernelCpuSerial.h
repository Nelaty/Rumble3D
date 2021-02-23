#pragma once
#include <R3D/Water/SPHEngine/Kernel/ISPHKernel.h>
#include <R3D/Common/Common.h>

namespace r3
{
    class R3D_DECLSPEC PressureKernelCpuSerial : public ISPHKernel
    {
    public:
        explicit PressureKernelCpuSerial() = default;
        ~PressureKernelCpuSerial() = default;

        void execute(const SPHContext_Ptr &context) override;
    };
}




