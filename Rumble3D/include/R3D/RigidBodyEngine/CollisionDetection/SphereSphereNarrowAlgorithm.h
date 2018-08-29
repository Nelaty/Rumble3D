#pragma once
#include "ISphereSphereNarrowAlgorithm.h"

namespace rum
{
	class SphereSphereNarrowAlgorithm : public ISphereSphereNarrowAlgorithm
	{
	public:
		explicit SphereSphereNarrowAlgorithm();
		~SphereSphereNarrowAlgorithm();

		bool generateContactData(CollisionSphere* first,
								 CollisionSphere* second,
								 CollisionData& collisionData) override;
	};
}
