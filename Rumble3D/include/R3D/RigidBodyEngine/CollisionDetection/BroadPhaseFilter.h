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

		void generateCollisions(const std::vector<RigidBody*>& rigidBodies,
								BroadPhaseCollisionData& data) override;

	private:
		bool createBroadPhaseCollision(RigidBody* first,
									   RigidBody* second,
									   BroadPhaseCollisionData& data);
	};
}
