#pragma once
#include "R3D/PhysicsEngineModule.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/ParticleForceRegistry.h"

#include <vector>
#include <memory>

namespace rum 
{
	class Particle;
	class ParticleContact;
	class ParticleContactGenerator;
	class ParticleContactResolver;

	class ParticleWorld : public PhysicsEngineModule
	{
	public:
		using Particles = std::vector<Particle*>;
		using ContactGenerators = std::vector<ParticleContactGenerator*>;

	public:
		/** Teilchen-Simulator mit maxContacts Kontakten und einer
		 * optionalen Anzahl Iterationen. Falls iterations == 0, dann
		 * werden 2 * Anzahl der Kontakte Iterationen durchgeführt.
		 */
		explicit ParticleWorld(unsigned int maxContacts, unsigned int iterations = 0);
		~ParticleWorld();
	
		/** Initializations for a single frame (tick) */
		void onBegin() override;
		void reset() override;

		void step(real timeDelta) override;
		void integrate(real timeDelta) override;

		/** Add another particle */
		void addParticle(Particle* p);
		/** Remove a specific particle */
		void removeParticle(Particle* p);
		/** Remove all particles */
		void removeAllParticles();

		/** Add another contact generator */
		void addContactGenerator(ParticleContactGenerator* pcg);
		/** Remove a specific contact generator */
		void removeContactGenerator(ParticleContactGenerator* pcg);
		/** Remove all contact generators */
		void removeAllContactGenerators();

		/** Needed to bind particles to particle force generators */
		ParticleForceRegistry& getParticleForceRegistry();

	private:
		unsigned int generateContacts();
		void runCollisionSolver(real timeDelta);

		Particles m_particles;
		ParticleForceRegistry m_registry;

		std::unique_ptr<ParticleContactResolver> m_resolver;
		ContactGenerators m_contactGenerators;
		ParticleContact* m_contacts;

		unsigned int m_maxContacts;
		bool m_calculateIterations;
		/** For ParticleContactResolver */
		unsigned int m_iterations;
	};
}