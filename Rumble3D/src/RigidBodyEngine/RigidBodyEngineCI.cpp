#include "R3D/RigidBodyEngine/RigidBodyEngineCI.h"
#include "R3D/RigidBodyEngine/RigidBodyWorld.h"

namespace rum
{
	RigidBodyEngineCI::~RigidBodyEngineCI()
	= default;

	void RigidBodyEngineCI::setRigidBodyWorld(RigidBodyWorld* rigidBodyWorld)
	{
		m_rigidBodyWorld = rigidBodyWorld;
	}

	RigidBodyWorld* RigidBodyEngineCI::getRigidBodyWorld() const
	{
		return m_rigidBodyWorld;
	}

	RigidBodyEngineCI::RigidBodyEngineCI(RigidBodyWorld* rigidBodyWorld)
		: m_rigidBodyWorld{rigidBodyWorld}
	{
	}
}
