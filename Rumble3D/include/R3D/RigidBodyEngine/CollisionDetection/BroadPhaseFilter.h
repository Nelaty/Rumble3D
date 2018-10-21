#pragma once
#include "IBroadPhaseFilter.h"

#include "R3D/Common/Common.h"

namespace r3
{
	class R3D_DECLSPEC BroadPhaseFilter : public IBroadPhaseFilter
	{
	public:
		explicit BroadPhaseFilter();
		~BroadPhaseFilter();

		void generateCollisions(const std::vector<RigidBody*>& rigidBodies,
								FixedSizeContainer<CollisionPair>& data) override;

	private:
		bool createBroadPhaseCollision(RigidBody* first,
									   RigidBody* second,
									   FixedSizeContainer<CollisionPair>& data);
	};
}
