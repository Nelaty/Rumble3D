#pragma once
#include "R3D/Common/Common.h"
#include "IBoxBoxNarrowAlgorithm.h"

namespace r3
{
	class R3D_DECLSPEC BoxBoxNarrowAlgorithm : public IBoxBoxNarrowAlgorithm
	{
	public:
		explicit BoxBoxNarrowAlgorithm();
		~BoxBoxNarrowAlgorithm();

	protected:
		bool generateContactDataImpl(RigidBody* rbBox1, CollisionBox* box1,
									 RigidBody* rbBox2, CollisionBox* box2,
									 CollisionData& collisionData) override;
	};
}