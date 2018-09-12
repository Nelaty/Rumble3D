#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class CollisionBox;

	class R3D_DECLSPEC IBoxBoxNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IBoxBoxNarrowAlgorithm();

		bool generateContactData(CollisionPrimitive* first, 
								 CollisionPrimitive* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactData(CollisionBox* first,
										 CollisionBox* second,
										 CollisionData& collisionData) = 0;

		explicit IBoxBoxNarrowAlgorithm();
	};
}