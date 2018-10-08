#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class CollisionSphere;

	class R3D_DECLSPEC ISphereSphereNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~ISphereSphereNarrowAlgorithm();

		bool generateContactData(RigidBody* first,
								 RigidBody* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactDataImpl(RigidBody* rbSphere1, CollisionSphere* sphere1,
											 RigidBody* rbSphere2, CollisionSphere* sphere2,
											 CollisionData& collisionData) = 0;

		explicit ISphereSphereNarrowAlgorithm();
	};
}