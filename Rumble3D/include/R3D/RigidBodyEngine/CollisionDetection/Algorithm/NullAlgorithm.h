#pragma once
#include <R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h>
#include <R3D/Common/Common.h>

namespace r3
{
	class R3D_DECLSPEC NullAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		explicit NullAlgorithm() = default;
		~NullAlgorithm() = default;

		bool generateContactData(RigidBody* first,
								 RigidBody* second, 
								 CollisionData& collisionData) override;
	};
}
