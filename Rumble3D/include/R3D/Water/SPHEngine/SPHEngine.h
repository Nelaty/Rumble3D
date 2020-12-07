//
// Created by root on 25.09.20.
//

#pragma once

#include <memory>

#include "R3D/PhysicsEngineModule.h"
#include "SPHEngineComputationInterfaceBase.h"

namespace r3
{
    class SPHSystem;
    class SPHContext;
    struct SPHParams;

    class SPHEngine : public PhysicsEngineModule
    {
    public:
        using ComputationInterface_Ptr = std::shared_ptr<SPHEngineComputationInterfaceBase>;
        using System_Ptr = std::shared_ptr<SPHSystem>;
        using Context_Ptr = std::shared_ptr<SPHContext>;
        using Params_Ptr = std::shared_ptr<SPHParams>;

        explicit SPHEngine();
        ~SPHEngine() = default;

        void setComputationInterface(const ComputationInterface_Ptr& ci);
        IComputationInterface* getComputationInterface() const override;

        void setContext(const Context_Ptr& context);
        const Context_Ptr& getContext() const;

        void setSystem(const System_Ptr& system);
        const System_Ptr& getSystem() const;

        void setParams(const Params_Ptr& params);
        const Params_Ptr& getParams() const;

    private:
        Context_Ptr m_context;

        ComputationInterface_Ptr m_computationInterface;
    };
}



