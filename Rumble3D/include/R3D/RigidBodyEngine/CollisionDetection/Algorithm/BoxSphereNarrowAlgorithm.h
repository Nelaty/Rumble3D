#pragma once
#include "R3D/Common/Common.h"
#include "IBoxSphereNarrowAlgorithm.h"

namespace r3
{
	/**
	 * \brief Default implementation for a box-sphere narrow algorithm.
	 */
	class R3D_DECLSPEC BoxSphereNarrowAlgorithm : public IBoxSphereNarrowAlgorithm
	{
	public:
		explicit BoxSphereNarrowAlgorithm();
		~BoxSphereNarrowAlgorithm();

	protected:
		bool generateContactDataImpl(RigidBody* rbBox, CollisionBox* box,
									 RigidBody* rbSphere, CollisionSphere* sphere,
									 CollisionData& collisionData) override;

	};
}
