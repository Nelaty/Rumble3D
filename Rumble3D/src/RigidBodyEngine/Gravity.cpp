#include "R3D/RigidBodyEngine/Gravity.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace rum
{
	Gravity::Gravity(const glm::vec3& gravity)
		: m_gravity(gravity)
	{
	}
	
	Gravity::~Gravity()
	{
	}

	void Gravity::UpdateForce(RigidBody* body, real duration)
	{
		if(!body->hasFiniteMass())
		{
			return;
		}
	
		body->addForce(m_gravity * body->getMass());
	}
}
