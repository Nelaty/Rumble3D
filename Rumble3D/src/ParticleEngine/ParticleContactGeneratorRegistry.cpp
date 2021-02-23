#include "R3D/ParticleEngine/ParticleContactGeneratorRegistry.h"

#include <algorithm>

namespace r3
{
	void ParticleContactGeneratorRegistry::registerContactGenerator(ParticleContactGenerator* generator)
	{
		m_contactGenerators.emplace_back(generator);
	}

	void ParticleContactGeneratorRegistry::unregisterContactGenerator(ParticleContactGenerator* generator)
	{
	    m_contactGenerators.erase(
	        std::remove(m_contactGenerators.begin(),
	            m_contactGenerators.end(),
	            generator),
		    m_contactGenerators.end());
	}

	void ParticleContactGeneratorRegistry::clear()
	{
		m_contactGenerators.clear();
	}

	const std::vector<ParticleContactGenerator*>& ParticleContactGeneratorRegistry::getGenerators() const
	{
		return m_contactGenerators;
	}
}
