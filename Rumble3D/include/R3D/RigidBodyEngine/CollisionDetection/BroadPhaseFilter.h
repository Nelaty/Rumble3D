#pragma once
#include "IBroadPhaseFilter.h"

namespace rum
{
	class BroadPhaseFilter : public IBroadPhaseFilter
	{
	public:
		explicit BroadPhaseFilter();
		~BroadPhaseFilter();

		std::vector<BroadPhaseCollision> generateCollisions(
			const std::vector<RigidBody*>& rigidBodies) override;
	};
}
