#pragma once

namespace rum
{
	class RigidBody;

	struct BroadPhaseCollision
	{
		RigidBody* m_first;
		RigidBody* m_second;
	};
}