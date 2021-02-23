#include "R3D/RigidBodyEngine/RigidBodyWorld.h"

#include "R3D/RigidBodyEngine/ForceGenerator.h"
#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/RigidBodyEngineCI.h"

#include <algorithm>

namespace r3
{
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
		m_rigidBodies.emplace_back(body);
	}

	void RigidBodyWorld::removeRigidBody(RigidBody* body)
	{
	    m_rigidBodies.erase(
	        std::remove(m_rigidBodies.begin(),
	            m_rigidBodies.end(),
	            body),
            m_rigidBodies.end());
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