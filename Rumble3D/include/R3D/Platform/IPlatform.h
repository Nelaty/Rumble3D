//
// Created by root on 26.09.20.
//

#pragma once
#include <R3D/Common/Common.h>

namespace r3
{
    class R3D_DECLSPEC IPlatform
    {
    public:
        virtual ~IPlatform() = default;


    protected:
        explicit IPlatform() = default;
    };
}



