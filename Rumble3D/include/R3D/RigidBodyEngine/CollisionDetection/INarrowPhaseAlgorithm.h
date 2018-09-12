#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class R3D_DECLSPEC INarrowPhaseAlgorithm
	{
	public:
		virtual ~INarrowPhaseAlgorithm();

		virtual bool generateContactData(CollisionPrimitive* first,
										 CollisionPrimitive* second,
										 CollisionData& collisionData) = 0;

	protected:
		explicit INarrowPhaseAlgorithm();
	};
}
