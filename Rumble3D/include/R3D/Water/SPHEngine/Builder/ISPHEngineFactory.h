//
// Created by root on 26.09.20.
//

#pragma once
#include <R3D/Water/SPHEngine/SPHEngine.h>
#include <R3D/Common/Common.h>

#include <memory>

namespace r3
{
    class R3D_DECLSPEC ISPHEngineFactory
    {
    public:
        virtual ~ISPHEngineFactory() = default;

        virtual std::shared_ptr<SPHEngine> create() = 0;

    protected:
        explicit ISPHEngineFactory() = default;
    };
}



