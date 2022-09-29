#include "R3D/ParticleEngine/ParticleDef.h"

#include <limits>

namespace r3
{
	void ParticleDef::setMass(const real mass)
	{
		m_inverseMass = mass != 0 ? static_cast<real>(1) / mass : std::numeric_limits<real>::max();
	}

	void ParticleDef::setInfiniteMass()
	{
		m_inverseMass = real(0);
	}
}
