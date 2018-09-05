#include "R3D/RigidBodyEngine/RigidBodyEngineCI.h"
#include "R3D/RigidBodyEngine/RigidBodyWorld.h"
#include "R3D/RigidBodyEngine/CollisionResolution/ICollisionResolverAccess.h"

namespace r3
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
		: m_collisionResolver{nullptr},
		m_rigidBodyWorld{rigidBodyWorld}
	{
	}
}
