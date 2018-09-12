#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrix.h"

namespace r3
{
	class R3D_DECLSPEC ServiceLocatorCollisionAlgorithmMatrix
	{
	public:
		static CollisionAlgorithmMatrix getMatrix();

	private:
		explicit ServiceLocatorCollisionAlgorithmMatrix();
		~ServiceLocatorCollisionAlgorithmMatrix();
	};
}
