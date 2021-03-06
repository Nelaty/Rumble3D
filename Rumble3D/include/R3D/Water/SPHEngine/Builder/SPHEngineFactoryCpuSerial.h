#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Water/SPHEngine/Builder/ISPHEngineFactory.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/DensityKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/ForceKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/PressureKernelCpuSerial.h"

namespace r3
{
    class R3D_DECLSPEC SPHEngineFactoryCpuSerial : public ISPHEngineFactory
    {
    public:
        explicit SPHEngineFactoryCpuSerial() = default;
        ~SPHEngineFactoryCpuSerial() = default;

        std::shared_ptr<SPHEngine> create() override;

    private:
        DensityKernelCpuSerial m_densityKernel;
        ForceKernelCpuSerial m_forceKernel;
        PressureKernelCpuSerial m_pressureKernel;
    };
}