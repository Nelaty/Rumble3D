#include "R3D/PhysicsEngineModule.h"

namespace r3
{
	PhysicsEngineModule::~PhysicsEngineModule()
	= default;

    PhysicsEngineModule::PhysicsEngineModule(std::string_view name)
        : m_enabled{true},
        m_name{name}
    {
    }

	void PhysicsEngineModule::enable(const bool enabled)
	{
		m_enabled = enabled;
	}

	bool PhysicsEngineModule::isEnabled() const
	{
		return m_enabled;
	}

	void PhysicsEngineModule::setName(std::string_view name)
    {
        m_name = name;
    }

    std::string_view PhysicsEngineModule::getName() const
    {
        return m_name;
    }
}