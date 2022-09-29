#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPair.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	class RigidBody;

	/**
	 * \brief Interface for broad phase filters. Only one broad phase
	 * filter can be used at the same time. To expand the broad phase
	 * look at IIntermediatePhaseFilter.
	 */
	class R3D_EXPORT IBroadPhaseFilter
	{
	public:
		virtual ~IBroadPhaseFilter() = default;

		/** 
		 * \brief Conservatively check, which rigid body pairs might 
		 * collide. These collisions can be false positives, but there 
		 * should never be false negatives.
		 * \param rigidBodies The rigid bodies to check against
		 * possible collisions.
		 * \param[out] data A number of possible collisions.
		 */
		virtual void generateCollisions(const std::vector<RigidBody*>& rigidBodies,
										FixedSizeContainer<CollisionPair>& data) = 0;

	protected:
		explicit IBroadPhaseFilter() = default;
	};
}