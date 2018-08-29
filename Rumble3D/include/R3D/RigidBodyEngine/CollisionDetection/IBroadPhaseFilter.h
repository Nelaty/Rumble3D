#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollision.h"

#include <vector>

namespace rum
{
	class RigidBody;

	class IBroadPhaseFilter
	{
	public:
		virtual ~IBroadPhaseFilter();

		/** 
		 * Conservatively check, which rigid body pairs might collide.
		 * These collisions can be false positives, but there should never
		 * be false negatives.
		 * \return A number of possible collisions.
		 */
		virtual std::vector<BroadPhaseCollision> generateCollisions(const std::vector<RigidBody*>& rigidBodies) = 0;

	protected:
		explicit IBroadPhaseFilter();
	};
}