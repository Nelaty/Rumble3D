#pragma once
#include "IPlaneBoxCollisionAlgorithm.h"

#include "R3D/Common/Common.h"

namespace r3
{
	/**
	 * \brief Default implementation for a plane-box narrow algorithm.
	 */
	class R3D_DECLSPEC PlaneBoxCollisionAlgorithm : public IPlaneBoxCollisionAlgorithm
	{
	public:
		explicit PlaneBoxCollisionAlgorithm();
		~PlaneBoxCollisionAlgorithm();

	protected:
		bool generateContactDataImpl(RigidBody* rbPlane,
									 CollisionPlane* plane, 
									 RigidBody* rbBox,
									 CollisionBox* box,
									 CollisionData& collisionData) override;
	};
}
