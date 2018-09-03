#include "R3D/RigidBodyEngine/ForceRegistry.h"
#include "R3D/RigidBodyEngine/ForceGenerator.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	void ForceRegistry::unregisterForce(RigidBody* rigidBody, ForceGenerator* fg)
	{
		auto i = m_registrations.begin();
		for (; i != m_registrations.end(); ++i)
		{
			if (i->m_rigidBody == rigidBody && i->m_forceGenerator == fg)
			{
				m_registrations.erase(i);
			}
		}
	}
	
	void ForceRegistry::clear()
	{
		m_registrations.clear();
	}

	ForceRegistry::ForceRegistry()
	= default;

	ForceRegistry::~ForceRegistry()
	= default;

	void ForceRegistry::registerForce(RigidBody* rigidBody, ForceGenerator* fg)
	{
		ForceRegistrationEntry registration{};
		registration.m_rigidBody = rigidBody;
		registration.m_forceGenerator = fg;
		m_registrations.push_back(registration);
	}
	
	void ForceRegistry::updateForces(const real duration)
	{
		for (auto& i : m_registrations)
		{
			i.m_forceGenerator->updateForce(i.m_rigidBody, duration);
		}
	}
}
