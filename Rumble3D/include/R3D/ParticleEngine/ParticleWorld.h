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
		ParticleWorld(unsigned int maxContacts, unsigned int iterations = 0);
		~ParticleWorld();
	
		/** Initializations for a single frame (tick) */
		virtual void OnBegin() override;
		virtual void Reset() override;

		virtual void Step(const real timeDelta) override;
		virtual void Integrate(real duration) override;

		/** Add another particle */
		void AddParticle(Particle* p);
		/** Remove a specific particle */
		void RemoveParticle(Particle* p);
		/** Remove all particles */
		void RemoveAllParticles();

		/** Add another contact generator */
		void AddContactGenerator(ParticleContactGenerator* pcg);
		/** Remove a specific contact generator */
		void RemoveContactGenerator(ParticleContactGenerator* pcg);
		/** Remove all contact generators */
		void RemoveAllContactGenerators();

		/** Needed to bind particles to particle force generators */
		ParticleForceRegistry& GetParticleForceRegistry();

	private:
		unsigned int GenerateContacts();
		void RunCollisionSolver(real duration);

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