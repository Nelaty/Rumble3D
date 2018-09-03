#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3 
{
	class RigidBody;

	class R3D_DECLSPEC ForceGenerator
	{
	public:
		virtual ~ForceGenerator();

		virtual void updateForce(RigidBody* body, real duration);

	protected:
		explicit ForceGenerator();
	};
}
