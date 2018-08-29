#pragma once
#include "R3D/PhysicsEngineModule.h"
#include "R3D/Common/Common.h"
#include "R3D/ParticleEngine/ParticleForceRegistry.h"
#include "R3D/ParticleEngine/ParticleContactGeneratorRegistry.h"

#include <vector>

namespace rum 
{
	class Particle;
	class ParticleContactGenerator;

	class ParticleEngineCI; 

	/**
	 * \brief ParticleWorld holds a number of particles and contact generators
	 */
	class R3D_DECLSPEC ParticleWorld : public PhysicsEngineModule
	{
	public:
		using Particles = std::vector<Particle*>;

		explicit ParticleWorld();
		~ParticleWorld();
	
		void setComputationInterface(ParticleEngineCI* computationInterface);
		IComputationInterface* getComputationInterface() const override;

		/** Register another particle */
		void registerParticle(Particle* p);
		/** Unregister a specific particle */
		void unregisterParticle(Particle* p);
		/** Unregister all particles */
		void unregisterAllParticles();

		/** Needed to bind particles to particle force generators */
		ParticleForceRegistry& getParticleForceRegistry();
		/** Needed to bind particles to particle force generators */
		const ParticleForceRegistry& getParticleForceRegistry() const;

		/** Get all currently registered particles. */
		Particles& getParticles();
		/** Get all currently registered particles. */
		const Particles& getParticles() const;

		/** Get the registry which holds all currently active contact generators. */
		ParticleContactGeneratorRegistry& getContactGeneratorRegistry();
		/** Get the registry which holds all currently active contact generators. */
		const ParticleContactGeneratorRegistry& getContactGeneratorRegistry() const;

	private:
		ParticleEngineCI* m_computationInterface{};

		ParticleForceRegistry m_forceRegistry;
		ParticleContactGeneratorRegistry m_contactGeneratorRegistry;

		Particles m_particles;
	};
}