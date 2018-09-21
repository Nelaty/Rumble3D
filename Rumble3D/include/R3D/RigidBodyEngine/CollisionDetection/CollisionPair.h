#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	class RigidBody;

	struct R3D_DECLSPEC CollisionPair
	{
		RigidBody* operator[](const int index)
		{
			return index == 0 ? m_first : m_second;
		}

		RigidBody* m_first;
		RigidBody* m_second;
	};
}