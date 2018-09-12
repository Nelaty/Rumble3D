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

	RigidBody* RigidBodyWorld::createRigidBody(const RigidBodyDef definition)
	{
		auto rigidBody = new RigidBody(definition);
		m_rigidBodies.emplace_back(rigidBody);
		return rigidBody;
	}

	bool RigidBodyWorld::destroyRigidBody(RigidBody* particle)
	{
		const auto removedBody = std::remove(m_rigidBodies.begin(),
											 m_rigidBodies.end(),
											 particle);

		if(removedBody != m_rigidBodies.end())
		{
			delete *removedBody;
			return true;
		}
		return false;
	}

	void RigidBodyWorld::destroyAllRigidBodies()
	{
		for(auto& it : m_rigidBodies)
		{
			delete it;
		}
		m_rigidBodies.clear();
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