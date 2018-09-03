#pragma once
#include "ForceGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC DirectedForce : public ForceGenerator
	{
	public:
		DirectedForce(glm::vec3 localPosition, glm::vec3 force);
		~DirectedForce();
		
		void updateForce(RigidBody* body, real duration) override;
		
		void setForce(const glm::vec3& force);
		
	private:
		glm::vec3 m_force;
		glm::vec3 m_localPosition;
	};
}
