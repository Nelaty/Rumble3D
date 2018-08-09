#pragma once
#include "ForceGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class RigidBody;

	class DirectedForce : public ForceGenerator
	{
	public:
		DirectedForce(glm::vec3 localPosition, glm::vec3 force);
		~DirectedForce();
		
		void UpdateForce(RigidBody* body, real duration) override;
		
		void SetForce(const glm::vec3& force);
		
	private:
		glm::vec3 m_force;
		glm::vec3 m_localPosition;
	};
}
