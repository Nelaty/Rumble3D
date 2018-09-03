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

		bool generateContactData(CollisionSphere* first,
								 CollisionSphere* second,
								 CollisionData& collisionData) override;
	};
}
