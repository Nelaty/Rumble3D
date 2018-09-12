#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollisionData.h"

#include <vector>

namespace r3
{
	class R3D_DECLSPEC IIntermediatePhaseFilter
	{
	public:
		virtual ~IIntermediatePhaseFilter();

		/**
		 * Further filter a previous set of collisions, which might
		 * still contain false negatives.
		 */
		virtual void generateCollisions(BroadPhaseCollisionData& collisions) = 0;

	protected:
		explicit IIntermediatePhaseFilter();
	};
}