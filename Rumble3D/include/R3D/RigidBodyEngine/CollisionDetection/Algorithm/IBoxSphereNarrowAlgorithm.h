#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class CollisionBox;
	class CollisionSphere;

	/**
	 * \brief Interface for box-sphere narrow algorithms.
	 */
	class R3D_DECLSPEC IBoxSphereNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IBoxSphereNarrowAlgorithm() = default;

		bool generateContactData(RigidBody* first,
								 RigidBody* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactDataImpl(RigidBody* rbBox, CollisionBox* box,
											 RigidBody* rbSphere, CollisionSphere* sphere,
											 CollisionData& collisionData) = 0;

		explicit IBoxSphereNarrowAlgorithm() = default;
	};
}