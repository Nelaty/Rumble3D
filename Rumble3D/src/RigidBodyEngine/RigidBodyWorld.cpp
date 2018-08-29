#include "R3D/RigidBodyEngine/RigidBodyWorld.h"

#include "R3D/RigidBodyEngine/ForceGenerator.h"
#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/RigidBodyEngineCI.h"

#include <algorithm>

namespace rum
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

	void RigidBodyWorld::registerRigidBody(RigidBody* rb)
	{
		m_rigidBodies.push_back(rb);
	}
	
	bool RigidBodyWorld::unregisterRigidBody(RigidBody* rb)
	{
		const auto removedRigidBody = std::remove(m_rigidBodies.begin(),
												  m_rigidBodies.end(),
												  rb);

		return removedRigidBody != m_rigidBodies.end();
	}
	
	void RigidBodyWorld::unregisterAllRigidBodies()
	{
		m_rigidBodies.clear();
	}

	RigidBodyWorld::RigidBodies& RigidBodyWorld::getRigidBodies()
	{
		return m_rigidBodies;
	}

	const RigidBodyWorld::RigidBodies& RigidBodyWorld::getRigidBodies() const
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