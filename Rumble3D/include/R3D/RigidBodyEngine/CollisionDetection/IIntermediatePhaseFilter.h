#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollision.h"

#include <vector>

namespace rum
{
	class IIntermediatePhaseFilter
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