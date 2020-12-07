//
// Created by root on 25.09.20.
//

#include "R3D/Water/SPHEngine/SPHEngineComputationInterfaceBase.h"
#include "R3D/Water/SPHEngine/SPHEngine.h"

namespace r3
{
    void SPHEngineComputationInterfaceBase::setSPHEngine(const SPHEngine_Ptr& engine)
    {
        m_sphEngine = engine;
    }

    SPHEngineComputationInterfaceBase::SPHEngineComputationInterfaceBase(const SPHEngine_Ptr& engine)
    {
        m_sphEngine = engine;
    }

    SPHEngine* SPHEngineComputationInterfaceBase::getSPHEngine() const
    {
        return m_sphEngine.get();
    }
}