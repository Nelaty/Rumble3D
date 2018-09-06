#pragma once
#include "R3D/PhysicsEngineModule.h"
#include "R3D/Common/Common.h"

#include "R3D/ParticleEngine/ParticleDef.h"
#include "R3D/ParticleEngine/ParticleForceRegistry.h"
#include "R3D/ParticleEngine/ParticleContactGeneratorRegistry.h"

#include <vector>

namespace r3 
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
		using Particle_Ptr = Particle*;
		using Particle_Container = std::vector<Particle_Ptr>;

		explicit ParticleWorld();
		~ParticleWorld();
	
		void setComputationInterface(ParticleEngineCI* computationInterface);
		IComputationInterface* getComputationInterface() const override;

		/** 
		 * \brief Allocate space for a new particle and register it.
		 * \param definition Construction information for the new particle.
		 * \return The new particle.
		 */
		Particle* createParticle(ParticleDef definition);
		/**
		 * \brief Free memory of a particle.
		 * \param particle The particle to destroy.
		 * \return True if the particle was found, false otherwise.
		 */
		bool destroyParticle(Particle* particle);
		/**
		 * \brief Free memory of all particles.
		 */
		void destroyAllParticles();

		/** Needed to bind particles to particle force generators */
		ParticleForceRegistry& getParticleForceRegistry();
		/** Needed to bind particles to particle force generators */
		const ParticleForceRegistry& getParticleForceRegistry() const;

		/** Get all currently registered particles. */
		Particle_Container& getParticles();
		/** Get all currently registered particles. */
		const Particle_Container& getParticles() const;

		/** Get the registry which holds all currently active contact generators. */
		ParticleContactGeneratorRegistry& getContactGeneratorRegistry();
		/** Get the registry which holds all currently active contact generators. */
		const ParticleContactGeneratorRegistry& getContactGeneratorRegistry() const;

	private:
		ParticleEngineCI* m_computationInterface{};

		ParticleForceRegistry m_forceRegistry;
		ParticleContactGeneratorRegistry m_contactGeneratorRegistry;

		Particle_Container m_particles;
	};
}