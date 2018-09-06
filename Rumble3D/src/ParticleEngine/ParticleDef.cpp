#include "R3D/ParticleEngine/ParticleDef.h"

namespace r3
{
	void ParticleDef::setMass(const real mass)
	{
		if (mass != 0)
		{
			m_inverseMass = static_cast<real>(1.0f) / mass;
		}
		else
		{
			m_inverseMass = static_cast<real>(R3D_REAL_MAX);
		}
	}

	void ParticleDef::setInfiniteMass()
	{
		m_inverseMass = static_cast<real>(1.0f);
	}
}
