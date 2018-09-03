#pragma once
#include "R3D/Common/Common.h"
#include "IBoxSphereNarrowAlgorithm.h"

namespace r3
{
	class R3D_DECLSPEC BoxSphereNarrowAlgorithm : public IBoxSphereNarrowAlgorithm
	{
	public:
		explicit BoxSphereNarrowAlgorithm();
		~BoxSphereNarrowAlgorithm();

		bool generateContactData(CollisionBox* first,
								 CollisionSphere* second,
								 CollisionData& collisionData) override;
	};
}
