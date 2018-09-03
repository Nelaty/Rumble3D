#pragma once
#include "ForceGenerator.h"

#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3 
{
	class RigidBody;

	class R3D_DECLSPEC Gravity : public ForceGenerator
	{
	public:
		explicit Gravity(const glm::vec3& gravity);
		~Gravity();

		void updateForce(RigidBody* body, real timeDelta) override;
	
	protected:
		glm::vec3 m_gravity;
	};
}