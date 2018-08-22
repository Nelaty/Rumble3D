#pragma once
#include "R3D/Common/Precision.h"

namespace rum 
{
	class RigidBody;

	class ForceGenerator
	{
	public:
		virtual ~ForceGenerator();

		virtual void updateForce(RigidBody* body, real duration);

	protected:
		explicit ForceGenerator();
	};
}
