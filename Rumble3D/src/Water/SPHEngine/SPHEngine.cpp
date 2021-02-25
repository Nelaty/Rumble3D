#include "R3D/Water/SPHEngine/SPHEngine.h"
#include "R3D/Water/SPHEngine/Entity/SPHContext.h"
#include "R3D/IComputationInterface.h"

namespace r3
{
    IComputationInterface* SPHEngine::getComputationInterface() const
    {
        return m_computationInterface.get();
    }

    void SPHEngine::setComputationInterface(const SPHEngine::ComputationInterface_Ptr& ci)
    {
        m_computationInterface = ci;
    }

    SPHEngine::SPHEngine()
    {
        m_context = std::make_shared<SPHContext>();
    }

    void SPHEngine::setContext(const SPHEngine::Context_Ptr& context)
    {
        m_context = context;
    }

    const SPHEngine::Context_Ptr& SPHEngine::getContext() const
    {
        return m_context;
    }

    void SPHEngine::setSystem(const SPHEngine::System_Ptr& system)
    {
        m_context->m_system = system;
    }

    const SPHEngine::System_Ptr& SPHEngine::getSystem() const
    {
        return m_context->m_system;
    }

    void SPHEngine::setParams(const SPHEngine::Params_Ptr& params)
    {
        m_context->m_params = params;
    }

    const SPHEngine::Params_Ptr& SPHEngine::getParams() const
    {
        return m_context->m_params;
    }
}
