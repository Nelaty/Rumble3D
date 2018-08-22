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
		explicit Gravity(const glm::vec3& gravity);
		~Gravity();

		void updateForce(RigidBody* body, real timeDelta) override;
	
	protected:
		glm::vec3 m_gravity;
	};
}