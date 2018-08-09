#pragma once
#include "ForceGenerator.h"

#include "R3D/Common/Precision.h"
#include <glm/glm.hpp>

namespace rum 
{
	class RigidBody;

	class Gravity :	public ForceGenerator
	{
	public:
		Gravity(const glm::vec3& gravity);
		~Gravity();

		virtual void UpdateForce(RigidBody* body, real duration) override;
	
	protected:
		glm::vec3 m_gravity;
	};
}