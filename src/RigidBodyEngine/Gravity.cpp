#include "R3D/RigidBodyEngine/Gravity.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	Gravity::Gravity(const glm::vec3& gravity)
		: m_gravity(gravity)
	{
	}

	void Gravity::updateForce(RigidBody* body, const real timeDelta)
	{
		if(!body->hasFiniteMass())
		{
			return;
		}

		// The mass factor is necessary, since it will be nullified later on
		// by inverse mass multiplication in the integration step.
		body->addForce(m_gravity * body->getMass());
	}
}
