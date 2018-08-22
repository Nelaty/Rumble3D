#include "R3D/RigidBodyEngine/RigidBodyWorld.h"
#include "R3D/RigidBodyEngine/CollisionDetector.h"

#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionData.h"
#include "R3D/RigidBodyEngine/ContactResolver.h"
#include "R3D/RigidBodyEngine/Contact.h"


namespace rum
{
	
	RigidBodyWorld::RigidBodyWorld(const unsigned maxContacts, const unsigned iterations)
		: m_maxContacts(maxContacts),
		m_iterations(iterations)
	{
		m_contacts = new Contact[maxContacts];
		m_calculateIterations = (iterations == 0);
		m_resolver = new ContactResolver(iterations);
		m_collisionData = new CollisionData();
		m_collisionData->reset(4);
	}
	
	RigidBodyWorld::~RigidBodyWorld()
	{
		delete[] m_contacts;
		delete m_resolver;
		delete m_collisionData;
	}
	
	void RigidBodyWorld::addRigidBody(RigidBody* rb)
	{
		m_rigidBodies.push_back(rb);
	}
	
	void RigidBodyWorld::addCollisionBox(CollisionBox* box)
	{
		m_collisionBoxes.push_back(box);
	}
	
	void RigidBodyWorld::addCollisionPrimitive(CollisionPrimitive* primitive)
	{
		m_collisionPrimitives.push_back(primitive);
	}
	
	void RigidBodyWorld::removeRigidBody(RigidBody* rb)
	{
		m_rigidBodies.remove(rb);
	}
	
	void RigidBodyWorld::removeAllRigidBodies()
	{
		m_rigidBodies.clear();
	}

	void RigidBodyWorld::addForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator)
	{
		m_registry.registerForce(rigidBody, forceGenerator);
	}

	void RigidBodyWorld::removeForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator)
	{
		m_registry.unregisterForce(rigidBody, forceGenerator);
	}

	void RigidBodyWorld::removeAllForceGenerators()
	{
		m_registry.clear();
	}

	ForceRegistry& RigidBodyWorld::getRigidBodyForceRegistry()
	{
		return m_registry;
	}
	
	void RigidBodyWorld::startFrame()
	{
		for (auto& rb : m_rigidBodies) 
		{
			rb->clearAccumulators();
			rb->calculateDerivedData();
		}
	}
	
	void RigidBodyWorld::runPhysics(const real timeDelta, unsigned& tmp)
	{
		m_registry.updateForces(timeDelta);
		integrate(timeDelta);
		return;
		// Prüfe auf Kontakte:

		//Hier Iteration über RigidBodies und ihre BoundingAreas
		//Je nachdem, welche Kombination, die richtige Methode von
		//detect aufrufen. Hier momentan nur 2 Boxen mit BoundingBoxes:
		CollisionBox * b1 = nullptr;
		CollisionBox * b2 = nullptr;
		auto i = 1;
		for (auto& box : m_collisionBoxes)
		{
			if (i == 1)
			{
				b1 = box; 
				i++;
			} 
			else 
			{
				b2 = box;
			}
		}
		
		tmp = CollisionDetector::boxAndBox(*b1, *b2, m_collisionData);
		// Resolve Kontakte:
		if (m_collisionData->getContactCount() > 0)
		{
			m_resolver->resolveContacts(m_collisionData->getContacts(), 1, timeDelta);
		}
	}
	
	void RigidBodyWorld::integrate(const real timeDelta)
	{
		for (auto& rb : m_rigidBodies) 
		{
			rb->integrate(timeDelta);
		}
	}
}