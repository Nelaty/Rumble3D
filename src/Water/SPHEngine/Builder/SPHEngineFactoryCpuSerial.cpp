//
// Created by root on 26.09.20.
//

#include <R3D/Water/SPHEngine/ComputationInterface/SPHEngineCICpuSerial.h>
#include "R3D/Water/SPHEngine/Builder/SPHEngineFactoryCpuSerial.h"

namespace r3
{
    std::shared_ptr<SPHEngine> SPHEngineFactoryCpuSerial::create()
    {
        auto engine = std::shared_ptr<SPHEngine>();
        auto computationInterface = std::make_shared<SPHEngineCICpuSerial>(engine);
        engine->setComputationInterface(computationInterface);
        return engine;
    }
}