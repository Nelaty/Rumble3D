#pragma once
#include "R3D/Common/Precision.h"
#include "CollisionPrimitive.h"

#include <glm/glm.hpp>

namespace rum
{
	class RigidBody;

	class CollisionSphere : public CollisionPrimitive
	{
	public:
		CollisionSphere(RigidBody * body, glm::mat4 offset, real radius); 
		~CollisionSphere();

		real GetRadius() const;

	protected:
		real m_radius;
	};
}
