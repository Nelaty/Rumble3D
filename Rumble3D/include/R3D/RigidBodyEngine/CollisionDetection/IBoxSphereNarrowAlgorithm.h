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

		bool generateContactData(CollisionPrimitive* first,
								 CollisionPrimitive* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactData(CollisionBox* first,
										 CollisionSphere* second,
										 CollisionData& collisionData) = 0;
		bool generateContactData(CollisionSphere* first,
								 CollisionBox* second,
								 CollisionData& collisionData);

		explicit IBoxSphereNarrowAlgorithm();
	};
}