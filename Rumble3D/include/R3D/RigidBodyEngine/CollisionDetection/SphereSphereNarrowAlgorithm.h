#pragma once
#include "R3D/Common/Common.h"
#include "ISphereSphereNarrowAlgorithm.h"

namespace r3
{
	class R3D_DECLSPEC SphereSphereNarrowAlgorithm : public ISphereSphereNarrowAlgorithm
	{
	public:
		explicit SphereSphereNarrowAlgorithm();
		~SphereSphereNarrowAlgorithm();

	protected:
		bool generateContactDataImpl(RigidBody* rbSphere1, CollisionSphere* sphere1,
									 RigidBody* rbSphere2, CollisionSphere* sphere2,
									 CollisionData& collisionData) override;
	};
}
