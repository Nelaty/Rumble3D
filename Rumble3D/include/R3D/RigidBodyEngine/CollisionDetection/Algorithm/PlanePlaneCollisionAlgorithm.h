#pragma once
#include "IPlanePlaneCollisionAlgorithm.h"

#include "R3D/Common/Common.h"

namespace r3
{
	/**
	 * \brief Default implementation for a plane-plane narrow algorithm.
	 */
	class R3D_DECLSPEC PlanePlaneCollisionAlgorithm : public IPlanePlaneCollisionAlgorithm
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
