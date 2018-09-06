#include "R3D/RigidBodyEngine/RigidBodyDef.h"

namespace r3
{
	void RigidBodyDef::setMass(const real mass)
	{
		if(mass != 0.0f)
		{
			m_inverseMass = static_cast<real>(1.0f) / mass;
		}
		else
		{
			m_inverseMass = static_cast<real>(R3D_REAL_MAX);
		}
	}

	void RigidBodyDef::setMassInfinite()
	{
		m_inverseMass = static_cast<real>(1.0f);
	}
}
