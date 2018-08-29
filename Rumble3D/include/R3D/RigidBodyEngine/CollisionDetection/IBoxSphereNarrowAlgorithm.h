#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace rum
{
	class CollisionBox;
	class CollisionSphere;

	class IBoxSphereNarrowAlgorithm : public INarrowPhaseAlgorithm
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