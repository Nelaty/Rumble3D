#pragma once
#include "CollisionPrimitive.h"

#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC CollisionSphere : public CollisionPrimitive
	{
	public:
		CollisionSphere(RigidBody* body, real radius, const glm::mat4& offset = glm::mat4(1));
		~CollisionSphere();

		real getRadius() const;

	protected:
	
		real m_radius;
	};
}
