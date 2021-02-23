#pragma once
#include "IPlaneSphereCollisionAlgorithm.h"

#include "R3D/Common/Common.h"

namespace r3
{
	/**
	 * \brief Default implementation for a plane-sphere narrow algorithm.
	 */
	class R3D_DECLSPEC PlaneSphereCollisionAlgorithm : public IPlaneSphereCollisionAlgorithm
	{
	public:
		explicit PlaneSphereCollisionAlgorithm() = default;
		~PlaneSphereCollisionAlgorithm() = default;

	protected:
		bool generateContactDataImpl(RigidBody* rbPlane, 
									 CollisionPlane* plane,
									 RigidBody* rbSphere,
									 CollisionSphere* sphere, 
									 CollisionData& collisionData) override;
	};
}
