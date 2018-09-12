#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollisionData.h"

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC IBroadPhaseFilter
	{
	public:
		virtual ~IBroadPhaseFilter();

		/** 
		 * Conservatively check, which rigid body pairs might collide.
		 * These collisions can be false positives, but there should never
		 * be false negatives.
		 * \return A number of possible collisions.
		 */
		virtual void generateCollisions(const std::vector<RigidBody*>& rigidBodies,
										BroadPhaseCollisionData& data) = 0;

	protected:
		explicit IBroadPhaseFilter();
	};
}