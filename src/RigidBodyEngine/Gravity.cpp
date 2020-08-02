#include "R3D/RigidBodyEngine/Gravity.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	Gravity::Gravity(const glm::vec3& gravity)
		: m_gravity(gravity)
	{
	}
	
	Gravity::~Gravity()
	= default;

	void Gravity::updateForce(RigidBody* body, const real timeDelta)
	{
		if(!body->hasFiniteMass())
		{
			return;
		}
	
		body->addForce(m_gravity * body->getMass());
	}
}
