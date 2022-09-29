#include "R3D/RigidBodyEngine/RigidBodyDef.h"

#include <limits>

namespace r3
{
	void RigidBodyDef::setMass(const real mass)
	{
		m_inverseMass = mass != 0.0f ? static_cast<real>(1) / mass : std::numeric_limits<real>::max();
	}

	void RigidBodyDef::setMassInfinite()
	{
		m_inverseMass = 0;
	}
}
