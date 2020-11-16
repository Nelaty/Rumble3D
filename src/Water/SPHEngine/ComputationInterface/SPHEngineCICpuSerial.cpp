#include "R3D/Water/SPHEngine/ComputationInterface/SPHEngineCICpuSerial.h"

namespace r3
{
    void SPHEngineCICpuSerial::onBegin()
    {
    }

    void SPHEngineCICpuSerial::step(real timeDelta)
    {
        auto context = m_sphEngine->getContext();

        m_densityKernel.execute(context);
        m_pressureKernel.execute(context);
        m_forceKernel.execute(context);
        m_boundaryKernel.execute(context);
    }

    void SPHEngineCICpuSerial::integrate(real timeDelta)
    {
        auto context = m_sphEngine->getContext();

        m_integrator.integrate(context, timeDelta);
    }

    void SPHEngineCICpuSerial::onEnd()
    {
    }

    void SPHEngineCICpuSerial::reset()
    {
    }

    SPHEngineCICpuSerial::SPHEngineCICpuSerial(const SPHEngine_Ptr& engine)
        : SPHEngineComputationInterfaceBase(engine)
    {
        m_boundaryKernel.setHalfSizes(glm::vec3(10.0));
    }
}