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
		using RigidBodies = std::list<RigidBody*>;
		using CollisionBoxes = std::list<CollisionBox*>;
		using CollisionPrimitives = std::list<CollisionPrimitive*>;
		
		RigidBodyWorld(unsigned maxContacts, unsigned iterations);
		~RigidBodyWorld();

		void integrate(real timeDelta) override;

		/* Add and unregisterForce rigid bodies */
		void addRigidBody(RigidBody* rb);
		void removeRigidBody(RigidBody* rb);
		void removeAllRigidBodies();
		
		/* Add and unregisterForce force generators */
		void addForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator);
		void removeForceGenerator(RigidBody* rigidBody, ForceGenerator* forceGenerator);
		void removeAllForceGenerators();

		void addCollisionBox(CollisionBox* box);
		void addCollisionPrimitive(CollisionPrimitive* primitive);
		// um Kraftgeneratoren an Teilchen binden zu können.
		ForceRegistry& getRigidBodyForceRegistry();

		// Die Engine:
		void startFrame();
		void runPhysics(real timeDelta, unsigned & tmp);

	private:
		RigidBodies m_rigidBodies;
		CollisionBoxes m_collisionBoxes;
		CollisionPrimitives m_collisionPrimitives;

		ForceRegistry m_registry;
		CollisionData* m_collisionData;
		ContactResolver* m_resolver;

		Contact* m_contacts;
		unsigned m_maxContacts;
		bool m_calculateIterations = true; // true: die Klasse berechnet Anzahl Iterationen.
		unsigned m_iterations; // Für den ParticleContactResolver.
	};

}