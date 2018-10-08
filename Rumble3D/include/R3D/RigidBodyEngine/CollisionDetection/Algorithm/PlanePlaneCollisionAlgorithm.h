#pragma once
#include "IPlanePlaneCollisionAlgorithm.h"

namespace r3
{
	class PlanePlaneCollisionAlgorithm : public IPlanePlaneCollisionAlgorithm
	{
	public:
		explicit PlanePlaneCollisionAlgorithm();
		~PlanePlaneCollisionAlgorithm();

	protected:
		bool generateContactDataImpl(RigidBody* rbPlane1,
									 CollisionPlane* plane1,
									 RigidBody* rbPlane2,
									 CollisionPlane* plane2,
									 CollisionData& collisionData) override;
	};
}
