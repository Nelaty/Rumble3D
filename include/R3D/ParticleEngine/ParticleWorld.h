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
	 * \brief A ParticleWorld is a physics engine module, used to
	 * simulate particles.
	 */
	class ParticleWorld : public PhysicsEngineModule
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
		* \brief Add an existent particle
		*/
		void addParticle(Particle* particle);
		/**
		 * \brief Remove a registered particle
		 * \return True if particle was registered, false otherwise.
		 */
		bool removeParticle(Particle* particle);

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