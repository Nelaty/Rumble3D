#pragma once
#include "IPlaneBoxCollisionAlgorithm.h"

namespace r3
{
	class PlaneBoxCollisionAlgorithm : public IPlaneBoxCollisionAlgorithm
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
