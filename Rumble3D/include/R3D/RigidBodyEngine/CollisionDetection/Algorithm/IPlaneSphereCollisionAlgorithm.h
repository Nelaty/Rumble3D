#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionPlane.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

#include "BoxBoxNarrowAlgorithm.h"

namespace r3
{
	class R3D_DECLSPEC IPlaneSphereCollisionAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IPlaneSphereCollisionAlgorithm();


		bool generateContactData(RigidBody* first, 
								 RigidBody* second, 
								 CollisionData& collisionData) override final;

	protected:
		explicit IPlaneSphereCollisionAlgorithm();

		virtual bool generateContactDataImpl(RigidBody* rbPlane, CollisionPlane* plane,
											 RigidBody* rbSphere, CollisionSphere* sphere,
											 CollisionData& collisionData) = 0;
	};
}
