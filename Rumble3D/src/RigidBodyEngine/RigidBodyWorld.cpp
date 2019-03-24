#include "R3D/RigidBodyEngine/RigidBodyWorld.h"

#include "R3D/RigidBodyEngine/ForceGenerator.h"
#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/RigidBodyEngineCI.h"

#include <algorithm>

namespace r3
{
	
	RigidBodyWorld::RigidBodyWorld()
	= default;

	RigidBodyWorld::~RigidBodyWorld()
	= default;

	void RigidBodyWorld::setComputationInterface(RigidBodyEngineCI* computationInterface)
	{
		m_computationInterface = computationInterface;
	}

	IComputationInterface* RigidBodyWorld::getComputationInterface() const
	{
		return m_computationInterface;
	}

	void RigidBodyWorld::addRigidBody(RigidBody* body)
	{
		m_rigidBodies.push_back(body);
	}

	bool RigidBodyWorld::removeRigidBody(RigidBody* body)
	{
		const auto removedIt = std::remove(m_rigidBodies.begin(),
										   m_rigidBodies.end(),
										   body);

		const bool found = removedIt != m_rigidBodies.end();
		if(found)
		{
			m_rigidBodies.erase(removedIt);
		}

		return found;
	}

	RigidBodyWorld::RigidBody_Container& RigidBodyWorld::getRigidBodies()
	{
		return m_rigidBodies;
	}

	const RigidBodyWorld::RigidBody_Container& RigidBodyWorld::getRigidBodies() const
	{
		return m_rigidBodies;
	}

	ForceRegistry& RigidBodyWorld::getForceRegistry()
	{
		return m_forceRegistry;
	}

	const ForceRegistry& RigidBodyWorld::getForceRegistry() const
	{
		return m_forceRegistry;
	}	
}