#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"

namespace r3
{
	class NullAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		explicit NullAlgorithm();
		~NullAlgorithm();

		bool generateContactData(RigidBody* first,
								 RigidBody* second, 
								 CollisionData& collisionData) override;
	};
}
