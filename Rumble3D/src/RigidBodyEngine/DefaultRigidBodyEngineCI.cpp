#include "R3D/RigidBodyEngine/DefaultRigidBodyEngineCI.h"
#include "R3D/RigidBodyEngine/RigidBodyWorld.h"
#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/CollisionResolution/CollisionResolver.h"
#include "R3D/RigidBodyEngine/CollisionDetection/NarrowPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseFilter.h"

#include <cmath>

namespace r3
{
	DefaultRigidBodyEngineCI::DefaultRigidBodyEngineCI()
	{
		init();
	}
	
	void DefaultRigidBodyEngineCI::onBegin()
	{
		assert(m_rigidBodyWorld != nullptr);

		auto& rigidBodies = m_rigidBodyWorld->getRigidBodies();
		for(auto& rb : rigidBodies)
		{
			rb->calculateDerivedData();
		}
	}

	void DefaultRigidBodyEngineCI::step(const real timeDelta)
	{
		assert(m_rigidBodyWorld != nullptr);

		auto forceRegistry = m_rigidBodyWorld->getForceRegistry();
		forceRegistry.updateForces(timeDelta);
	}

	void DefaultRigidBodyEngineCI::integrate(const real timeDelta)
	{	
		assert(m_rigidBodyWorld != nullptr);

		auto& rigidBodies = m_rigidBodyWorld->getRigidBodies();

		auto& collisionData = m_collisionDetector.generateCollisions(rigidBodies);
		m_collisionResolver->resolveCollisions(collisionData, timeDelta);

		for(auto& rb : rigidBodies)
		{
			rb->integrate(timeDelta);
		}
	}

	void DefaultRigidBodyEngineCI::onEnd()
	{
		assert(m_rigidBodyWorld != nullptr);

		auto& rigidBodies = m_rigidBodyWorld->getRigidBodies();
		for(auto& rb : rigidBodies)
		{
			rb->clearAccumulators();
		}
	}

	void DefaultRigidBodyEngineCI::reset()
	{
		assert(m_rigidBodyWorld != nullptr);
	}

	void DefaultRigidBodyEngineCI::init()
	{
		// Initialize collision detector
		auto broadPhaseFilter = std::make_unique<BroadPhaseFilter>();
		auto narrowPhaseFilter = std::make_unique<NarrowPhaseFilter>();

		m_collisionDetector.setBroadPhaseFilter(std::move(broadPhaseFilter));
		m_collisionDetector.setNarrowPhaseFilter(std::move(narrowPhaseFilter));

		// Initialize collision resolver
		m_collisionResolver = std::make_unique<CollisionResolver>();
	}
}
