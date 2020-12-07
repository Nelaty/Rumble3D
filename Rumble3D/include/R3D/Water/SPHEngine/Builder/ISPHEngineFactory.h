//
// Created by root on 26.09.20.
//

#pragma once

#include <memory>
#include <R3D/Water/SPHEngine/SPHEngine.h>

namespace r3
{
    class ISPHEngineFactory
    {
    public:
        virtual ~ISPHEngineFactory() = default;

        virtual std::shared_ptr<SPHEngine> create() = 0;

    protected:
        explicit ISPHEngineFactory() = default;
    };
}



