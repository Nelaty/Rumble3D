#include "R3D/PhysicsEngineModule.h"

namespace rum
{
	PhysicsEngineModule::~PhysicsEngineModule()
	{
	}

	PhysicsEngineModule::PhysicsEngineModule()
		: m_enabled{true}
	{
	}

	void PhysicsEngineModule::OnBegin()
	{
	}

	void PhysicsEngineModule::OnEnd()
	{
	}

	void PhysicsEngineModule::Enable(bool enabled)
	{
		m_enabled = enabled;
	}

	bool PhysicsEngineModule::IsEnabled() const
	{
		return m_enabled;
	}

}