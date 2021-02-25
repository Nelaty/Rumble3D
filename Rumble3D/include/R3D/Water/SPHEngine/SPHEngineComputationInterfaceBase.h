#pragma once
#include "R3D/Common/Common.h"
#include "R3D/IComputationInterface.h"

#include <memory>

namespace r3
{
    class SPHEngine;

    class R3D_DECLSPEC SPHEngineComputationInterfaceBase : public IComputationInterface
    {
    public:
        using SPHEngine_Ptr = std::shared_ptr<SPHEngine>;

        virtual ~SPHEngineComputationInterfaceBase() = default;

        void setSPHEngine(const SPHEngine_Ptr& engine);
        SPHEngine* getSPHEngine() const;

    protected:
        explicit SPHEngineComputationInterfaceBase(const SPHEngine_Ptr& engine = nullptr);

        std::shared_ptr<SPHEngine> m_sphEngine;
    };
}



