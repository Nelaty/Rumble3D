#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	class RigidBody;

	struct R3D_DECLSPEC BroadPhaseCollision
	{
		RigidBody* m_first;
		RigidBody* m_second;
	};
}