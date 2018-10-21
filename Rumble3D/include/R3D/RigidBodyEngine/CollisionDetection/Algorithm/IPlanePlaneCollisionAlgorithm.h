#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionPlane.h"

namespace r3
{
	class R3D_DECLSPEC IPlanePlaneCollisionAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IPlanePlaneCollisionAlgorithm();

		bool generateContactData(RigidBody* first, 
								 RigidBody* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactDataImpl(RigidBody* rbPlane1, CollisionPlane* plane1,
											 RigidBody* rbPlane2, CollisionPlane* plane2,
											 CollisionData& collisionData) = 0;

		explicit IPlanePlaneCollisionAlgorithm();
	};
}
