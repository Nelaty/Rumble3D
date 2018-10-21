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
	 * \brief A ParticleWorld holds a number of particles and contact generators.
	 * It uses its ParticleEngineCI to manipulate those particles.
	 */
	class R3D_DECLSPEC ParticleWorld : public PhysicsEngineModule
	{
	public:
		using Particle_Ptr = Particle*;
		using Particle_Container = std::vector<Particle_Ptr>;

		explicit ParticleWorld();
		~ParticleWorld();

		/**
		 * \brief Change the computation interface, used by the module.
		 * \param computationInterface The new computation interface.
		 */
		void setComputationInterface(ParticleEngineCI* computationInterface);
		/**
		 * \brief Get the module's computation interface.
		 * \return The currently used computation interface.
		 */
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

		/** 
		 * \brief Get the module's particle force registry
		 * \return The particle force registry
		 */
		ParticleForceRegistry& getParticleForceRegistry();
		/**
		 * \brief Get the module's particle force registry
		 * \return The particle force registry
	 	 */
		const ParticleForceRegistry& getParticleForceRegistry() const;

		/** 
		 * \brief Get the module's particles.
		 * \return All currently registered particles. 
		 */
		Particle_Container& getParticles();
		/**
		 * \brief Get the module's particles.
		 * \return All currently registered particles.
		 */
		const Particle_Container& getParticles() const;

		/** 
		 * \brief Get the module's particle contact generator registry.
		 * \return The particle contact generator registry
		 */
		ParticleContactGeneratorRegistry& getContactGeneratorRegistry();
		/**
		* \brief Get the module's particle contact generator registry.
		* \return The particle contact generator registry
		*/
		const ParticleContactGeneratorRegistry& getContactGeneratorRegistry() const;

	private:
		ParticleEngineCI* m_computationInterface{};

		ParticleForceRegistry m_forceRegistry;
		ParticleContactGeneratorRegistry m_contactGeneratorRegistry;

		Particle_Container m_particles;
	};
}