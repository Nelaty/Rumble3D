#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace rum
{
	class CollisionSphere;

	class ISphereSphereNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~ISphereSphereNarrowAlgorithm();

		virtual bool generateContactData(CollisionSphere* first,
										 CollisionSphere* second,
										 CollisionData& collisionData) = 0;

	protected:
		explicit ISphereSphereNarrowAlgorithm();
	};
}