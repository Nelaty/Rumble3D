#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollision.h"

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
		virtual std::vector<BroadPhaseCollision> generateCollisions(
			const std::vector<BroadPhaseCollision>& collisions) = 0;

	protected:
		explicit IIntermediatePhaseFilter();
	};
}