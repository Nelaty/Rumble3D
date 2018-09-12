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
		CollisionSphere(RigidBody* body, const glm::mat4& offset, real radius); 
		~CollisionSphere();

		real getRadius() const;

	protected:
	
		real m_radius;
	};
}
