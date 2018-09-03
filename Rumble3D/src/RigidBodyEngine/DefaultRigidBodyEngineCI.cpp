#include "R3D/RigidBodyEngine/DefaultRigidBodyEngineCI.h"
#include "R3D/RigidBodyEngine/RigidBodyWorld.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include "R3D/RigidBodyEngine/CollisionResolution/CollisionResolver.h"
#include "R3D/RigidBodyEngine/CollisionDetection/NarrowPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseFilter.h"

namespace r3
{
	DefaultRigidBodyEngineCI::DefaultRigidBodyEngineCI()
	{
		init();
	}

	DefaultRigidBodyEngineCI::~DefaultRigidBodyEngineCI()
	= default;

	void DefaultRigidBodyEngineCI::onBegin()
	{
		assert(m_rigidBodyWorld != nullptr);

		auto rigidBodies = m_rigidBodyWorld->getRigidBodies();
		for(auto& rb : rigidBodies)
		{
			rb->clearAccumulators();
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

		auto rigidBodies = m_rigidBodyWorld->getRigidBodies();

		//const auto& collisionData = m_collisionDetector.generateCollisions(rigidBodies);
		//m_collisionResolver->resolveCollisions(collisionData);
		
		for(auto& rb : rigidBodies)
		{
			rb->integrate(timeDelta);
		}
	}

	//void RigidBodyWorld::runPhysics(const real timeDelta, unsigned& tmp)
	//{
	//	m_registry.updateForces(timeDelta);
	//	//integrate(timeDelta);
	//	return;
	//	// Prüfe auf Kontakte:

	//	//Hier Iteration über RigidBodies und ihre BoundingAreas
	//	//Je nachdem, welche Kombination, die richtige Methode von
	//	//detect aufrufen. Hier momentan nur 2 Boxen mit BoundingBoxes:
	//	CollisionBox * b1 = nullptr;
	//	CollisionBox * b2 = nullptr;
	//	auto i = 1;
	//	for(auto& box : m_collisionBoxes)
	//	{
	//		if(i == 1)
	//		{
	//			b1 = box;
	//			i++;
	//		}
	//		else
	//		{
	//			b2 = box;
	//		}
	//	}

	//	tmp = CollisionDetectorOld::boxAndBox(*b1, *b2, m_collisionData);
	//	// Resolve Kontakte:
	//	if(m_collisionData->getContactCount() > 0)
	//	{
	//		m_resolver->resolveContacts(m_collisionData->getContacts(), 1, timeDelta);
	//	}
	//}

	void DefaultRigidBodyEngineCI::onEnd()
	{
		assert(m_rigidBodyWorld != nullptr);
	}

	void DefaultRigidBodyEngineCI::reset()
	{
		assert(m_rigidBodyWorld != nullptr);
	}

	void DefaultRigidBodyEngineCI::init()
	{
		auto broadPhaseFilter = std::make_unique<BroadPhaseFilter>();
		auto narrowPhaseFilter = std::make_unique<NarrowPhaseFilter>();

		m_collisionDetector.setBroadPhaseFilter(std::move(broadPhaseFilter));
		m_collisionDetector.setNarrowPhaseFilter(std::move(narrowPhaseFilter));
	}
}
