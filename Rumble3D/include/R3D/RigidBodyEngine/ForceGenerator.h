#pragma once
#include "R3D/Common/Precision.h"

namespace rum 
{
	class RigidBody;

	class ForceGenerator
	{
	public:
		virtual void UpdateForce(RigidBody* body, real duration) = 0;
	};
}
