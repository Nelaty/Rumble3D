#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Water/SPHEngine/Entity/SPHContext.h"

#include <memory>

namespace r3
{
    class R3D_DECLSPEC ISPHKernel
    {
    public:
        using SPHContext_Ptr = std::shared_ptr<SPHContext>;

        virtual ~ISPHKernel() = default;

        virtual void execute(const SPHContext_Ptr& context) = 0;

    protected:
        ISPHKernel() = default;
    };
}




