#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Water/SPHEngine/Entity/SPHContext.h"

namespace r3
{
    class R3D_DECLSPEC ISPHIntegrator
    {
    public:
        using SPHContext_Ptr = std::shared_ptr<SPHContext>;

        virtual ~ISPHIntegrator() = default;

        virtual void integrate(const SPHContext_Ptr& context, float timeDelta) = 0;

    protected:
        explicit ISPHIntegrator() = default;
    };
}



