#pragma once
#include "IPlaneSphereCollisionAlgorithm.h"

namespace r3
{
	class PlaneSphereCollisionAlgorithm : public IPlaneSphereCollisionAlgorithm
	{
	public:
		explicit PlaneSphereCollisionAlgorithm();
		~PlaneSphereCollisionAlgorithm();

	protected:
		bool generateContactDataImpl(RigidBody* rbPlane, 
									 CollisionPlane* plane,
									 RigidBody* rbSphere,
									 CollisionSphere* sphere, 
									 CollisionData& collisionData) override;
	};
}
