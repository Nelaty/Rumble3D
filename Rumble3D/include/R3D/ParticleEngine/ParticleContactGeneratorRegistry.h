#pragma once
#include "R3D/Common/Common.h"

#include <vector>

namespace r3
{
	class ParticleContactGenerator;

	/**
	 * \brief Registry for ParticleContactGenerators.
	 */
	class R3D_DECLSPEC ParticleContactGeneratorRegistry
	{
	public:
		explicit ParticleContactGeneratorRegistry() = default;
		~ParticleContactGeneratorRegistry() = default;

		/** 
		 * \brief Register a contact generator.
		 * \param generator The generator to be registered.
		 */
		void registerContactGenerator(ParticleContactGenerator* generator);
		/** 
		 * \brief Unregister a contact generator.
		 * \param generator The generator, which will be unregistered.
		 */
		void unregisterContactGenerator(ParticleContactGenerator* generator);
		/** 
		 * \brief Unregister all previously registered contact generators.
		 */
		void clear();

		/**
		 * \brief Get all generators in this registry.
		 * \return All registered generators.
		 */
		const std::vector<ParticleContactGenerator*>& getGenerators() const;
		
	protected:
		std::vector<ParticleContactGenerator*> m_contactGenerators;
	};
}
