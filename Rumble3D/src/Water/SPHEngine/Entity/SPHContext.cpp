#include "R3D/Water/SPHEngine/Entity/SPHContext.h"
#include "R3D/Water/SPHEngine/Entity/SPHSystem.h"
#include "R3D/Water/SPHEngine/Entity/SPHParams.h"

namespace r3
{
    SPHContext::SPHContext()
    {
        m_system = std::make_shared<SPHSystem>();
        m_params = std::make_shared<SPHParams>();
    }
}