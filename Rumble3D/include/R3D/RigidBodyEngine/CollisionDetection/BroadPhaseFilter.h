#pragma once
#include "R3D/Common/Common.h"
#include "IBroadPhaseFilter.h"

namespace r3
{
	class R3D_DECLSPEC BroadPhaseFilter : public IBroadPhaseFilter
	{
	public:
		explicit BroadPhaseFilter();
		~BroadPhaseFilter();

		std::vector<BroadPhaseCollision> generateCollisions(
			const std::vector<RigidBody*>& rigidBodies) override;
	};
}
