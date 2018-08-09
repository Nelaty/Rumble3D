#pragma once
#include "R3D/PhysicsEngineModule.h"
#include "R3D/Common/Precision.h"
#include "ForceRegistry.h"

#include <list>

namespace rum 
{
	class ForceGenerator;
	class RigidBody;
	class CollisionBox;
	class CollisionPrimitive;
	class CollisionData;
	class Contact;
	class ContactResolver;

	class RigidBodyWorld : public PhysicsEngineModule
	{
	public:
		typedef std::list<RigidBody*> RigidBodies;
		typedef std::list<CollisionBox*> CollisionBoxes;
		typedef std::list<CollisionPrimitive*> CollisionPrimitives;
		
	public:
		RigidBodyWorld(unsigned maxContacts, unsigned iterations);
		~RigidBodyWorld();

		void integrate(real duration);

		/* Add and remove rigid bodies */
		void addRigidBody(RigidBody* rb);
		void removeRigidBody(RigidBody* rb);
		void RemoveAllRigidBodies();
		
		/* Add and remove force generators */
		void AddForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator);
		void RemoveForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator);
		void RemoveAllForceGenerators();

		void addCollisionBox(CollisionBox* box);
		void addCollisionPrimitive(CollisionPrimitive* primitive);
		// um Kraftgeneratoren an Teilchen binden zu können.
		ForceRegistry *getRigidBodyForceRegistry();

		// Die Engine:
		void StartFrame();
		void runPhysics(const real duration, unsigned & tmp);

	private:
		RigidBodies m_rigidBodies;
		CollisionBoxes m_collisionBoxes;
		CollisionPrimitives m_collisionPrimitives;

		ForceRegistry m_registry;
		CollisionData* m_KollisionsDaten;
		ContactResolver* m_resolver;

		Contact* m_contacts;
		unsigned m_maxContacts;
		bool m_calculateIterations = true; // true: die Klasse berechnet Anzahl Iterationen.
		unsigned m_iterations; // Für den ParticleContactResolver.
	};

}