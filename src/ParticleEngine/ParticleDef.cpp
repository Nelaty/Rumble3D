#include "R3D/ParticleEngine/ParticleDef.h"

namespace r3
{
	void ParticleDef::setMass(const real mass)
	{
		if (mass != 0)
		{
			m_inverseMass = real(1) / mass;
		}
		else
		{
			m_inverseMass = real(R3D_REAL_MAX);
		}
	}

	void ParticleDef::setInfiniteMass()
	{
		m_inverseMass = real(0);
	}
}
