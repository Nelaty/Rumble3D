#pragma once
#include <vector>

namespace r3
{
	class ParticleContactGenerator;

	class ParticleContactGeneratorRegistry
	{
	public:
		explicit ParticleContactGeneratorRegistry();
		~ParticleContactGeneratorRegistry();

		/** Add another contact generator */
		void registerContactGenerator(ParticleContactGenerator* generator);
		/** 
		 * Remove a specific contact generator 
		 * \return True if the given generator was found and removed, false otherwise.
		 */
		bool unregisterContactGenerator(ParticleContactGenerator* generator);
		/** Remove all contact generators */
		void clear();

		const std::vector<ParticleContactGenerator*>& getGenerators() const;
		
	protected:
		std::vector<ParticleContactGenerator*> m_contactGenerators;
	};
}
