#pragma once
#include "ISphereSphereNarrowAlgorithm.h"

#include "R3D/Common/Common.h"

namespace r3
{
	/**
	 * \brief Default implementation for a sphere-sphere narrow algorithm.
	 */
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
