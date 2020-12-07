#pragma once

#include <R3D/Water/SPHEngine/Entity/SPHContext.h>

#include <memory>

namespace r3
{
    class ISPHKernel
    {
    public:
        using SPHContext_Ptr = std::shared_ptr<SPHContext>;

        virtual ~ISPHKernel() = default;

        virtual void execute(const SPHContext_Ptr& context) = 0;

    protected:
        ISPHKernel() = default;
    };
}




