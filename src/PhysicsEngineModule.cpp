#include "R3D/PhysicsEngineModule.h"

namespace r3
{
	PhysicsEngineModule::~PhysicsEngineModule()
	= default;

	PhysicsEngineModule::PhysicsEngineModule()
		: m_enabled{true}
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

}