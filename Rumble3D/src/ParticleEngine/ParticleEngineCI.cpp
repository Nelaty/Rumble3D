#include "R3D/ParticleEngine/ParticleEngineCI.h"

namespace r3
{
	void ParticleEngineCI::setParticleWorld(ParticleWorld* particleWorld)
	{
		m_particleWorld = particleWorld;
	}

	ParticleWorld* ParticleEngineCI::getParticleWorld() const
	{
		return m_particleWorld;
	}

	ParticleEngineCI::ParticleEngineCI(ParticleWorld* particleWorld)
		: m_particleWorld{particleWorld}
	{
	}
}
