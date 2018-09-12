#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	class CollisionSphere;

	class R3D_DECLSPEC ISphereSphereNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~ISphereSphereNarrowAlgorithm();

		bool generateContactData(CollisionPrimitive* first,
								 CollisionPrimitive* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactData(CollisionSphere* first,
										 CollisionSphere* second,
										 CollisionData& collisionData) = 0;

		explicit ISphereSphereNarrowAlgorithm();
	};
}