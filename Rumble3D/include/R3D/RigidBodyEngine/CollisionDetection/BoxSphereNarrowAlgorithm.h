#pragma once
#include "IBoxSphereNarrowAlgorithm.h"

namespace rum
{
	class BoxSphereNarrowAlgorithm : public IBoxSphereNarrowAlgorithm
	{
	public:
		explicit BoxSphereNarrowAlgorithm();
		~BoxSphereNarrowAlgorithm();

		bool generateContactData(CollisionBox* first,
								 CollisionSphere* second,
								 CollisionData& collisionData) override;
	};
}
