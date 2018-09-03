#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class CollisionBox;
	class CollisionSphere;

	class R3D_DECLSPEC IBoxSphereNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IBoxSphereNarrowAlgorithm();

		virtual bool generateContactData(CollisionBox* first,
										 CollisionSphere* second,
										 CollisionData& collisionData) = 0;

	protected:
		explicit IBoxSphereNarrowAlgorithm();
	};
}