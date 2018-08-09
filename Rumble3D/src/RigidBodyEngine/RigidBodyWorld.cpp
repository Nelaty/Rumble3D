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
	
	RigidBodyWorld::RigidBodyWorld(unsigned maxContacts, unsigned iterations)
		: m_maxContacts(maxContacts),
		m_iterations(iterations)
	{
		m_contacts = new Contact[maxContacts];
		m_calculateIterations = (iterations == 0);
		m_resolver = new ContactResolver(iterations);
		m_KollisionsDaten = new CollisionData();
		m_KollisionsDaten->reset(4);
	}
	
	RigidBodyWorld::~RigidBodyWorld()
	{
		delete[] m_contacts;
		delete m_resolver;
		delete m_KollisionsDaten;
	}
	
	void RigidBodyWorld::addRigidBody(RigidBody * rb)
	{
		m_rigidBodies.push_back(rb);
	}
	
	void RigidBodyWorld::addCollisionBox(CollisionBox * box)
	{
		m_collisionBoxes.push_back(box);
	}
	
	void RigidBodyWorld::addCollisionPrimitive(CollisionPrimitive * primitive)
	{
		m_collisionPrimitives.push_back(primitive);
	}
	
	void RigidBodyWorld::removeRigidBody(RigidBody * rb)
	{
		m_rigidBodies.remove(rb);
	}
	
	void RigidBodyWorld::RemoveAllRigidBodies()
	{
		m_rigidBodies.clear();
	}

	void RigidBodyWorld::AddForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator)
	{
		m_registry.Add(rigidBody, forceGenerator);
	}

	void RigidBodyWorld::RemoveForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator)
	{
		m_registry.Remove(rigidBody, forceGenerator);
	}

	void RigidBodyWorld::RemoveAllForceGenerators()
	{
		m_registry.Clear();
	}

	ForceRegistry * RigidBodyWorld::getRigidBodyForceRegistry()
	{
		return &m_registry;
	}
	
	void RigidBodyWorld::StartFrame()
	{
		for (RigidBody* rb : m_rigidBodies) 
		{
			rb->clearAccumulators();
			rb->calculateDerivedData();
		}
	}
	
	void RigidBodyWorld::runPhysics(const real duration, unsigned & tmp)
	{
		m_registry.UpdateForces(duration);
		integrate(duration);
		return;
		// Prüfe auf Kontakte:

		//Hier Iteration über RigidBodies und ihre BoundingAreas
		//Je nachdem, welche Kombination, die richtige Methode von
		//detect aufrufen. Hier momentan nur 2 Boxen mit BoundingBoxes:
		CollisionBox * b1 = nullptr;
		CollisionBox * b2 = nullptr;
		int i = 1;
		for (CollisionBox* box : m_collisionBoxes)
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
		
		tmp = CollisionDetector::boxAndBox(*b1, *b2, m_KollisionsDaten);
		// Resolve Kontakte:
		if (m_KollisionsDaten->getContactCount() > 0)
		{
			m_resolver->resolveContacts(m_KollisionsDaten->getContacts(), 1, duration);
		}
	}
	
	void RigidBodyWorld::integrate(real duration)
	{
		for (RigidBody* rb : m_rigidBodies) 
		{
			rb->integrate(duration);
		}
	}
}