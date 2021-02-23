#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class CollisionBox;

	/**
	 * \brief Interface for box-box narrow algorithms.
	 */
	class R3D_DECLSPEC IBoxBoxNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IBoxBoxNarrowAlgorithm() = default;

		bool generateContactData(RigidBody* first,
								 RigidBody* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactDataImpl(RigidBody* rbBox1, CollisionBox* box1,
											 RigidBody* rbBox2, CollisionBox* box2,
											 CollisionData& collisionData) = 0;

		explicit IBoxBoxNarrowAlgorithm() = default;
	};
}