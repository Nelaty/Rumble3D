#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Water/SPHEngine/SPHEngineComputationInterfaceBase.h"
#include "R3D/Water/SPHEngine/SPHEngine.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/PressureKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/ForceKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/DensityKernelCpuSerial.h"
#include "R3D/Water/SPHEngine/Integrator/Cpu/SPHIntegratorCpuSerial.h"
#include "R3D/Water/SPHEngine/Kernel/Cpu/BoundaryConditionKernelCpuSerial.h"

namespace r3
{
    class R3D_DECLSPEC SPHEngineCICpuSerial : public SPHEngineComputationInterfaceBase
    {
    public:
        explicit SPHEngineCICpuSerial(const SPHEngine_Ptr& engine = nullptr);
        ~SPHEngineCICpuSerial() = default;

        void onBegin()  override;
        void step(real timeDelta)  override;
        void integrate(real timeDelta)  override;
        void onEnd()  override;
        void reset() override;

    private:
        SPHIntegratorCpuSerial m_integrator;

        DensityKernelCpuSerial m_densityKernel;
        ForceKernelCpuSerial m_forceKernel;
        PressureKernelCpuSerial m_pressureKernel;
        BoundaryConditionKernelCpuSerial m_boundaryKernel;
    };
}