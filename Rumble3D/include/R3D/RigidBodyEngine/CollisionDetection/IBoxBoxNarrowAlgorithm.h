#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace rum
{
	class CollisionBox;

	class IBoxBoxNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IBoxBoxNarrowAlgorithm();

		virtual bool generateContactData(CollisionBox* first,
										 CollisionBox* second,
										 CollisionData& collisionData) = 0;

	protected:
		explicit IBoxBoxNarrowAlgorithm();
	};
}