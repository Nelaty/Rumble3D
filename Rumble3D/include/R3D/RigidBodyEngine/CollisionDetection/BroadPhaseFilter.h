#pragma once
#include "IBroadPhaseFilter.h"

#include "R3D/Common/Common.h"

namespace r3
{
	/**
	 * \brief Default implementation of IBroadPhaseFilter.
	 */
	class R3D_DECLSPEC BroadPhaseFilter : public IBroadPhaseFilter
	{
	public:
		explicit BroadPhaseFilter()  = default;
		~BroadPhaseFilter() = default;

		/**
		 * \brief Conservatively check, which rigid body pairs might
		 * collide. These collisions can be false positives, but there
		 * should never be false negatives.
		 * \param rigidBodies The rigid bodies to check against
		 * possible collisions.
		 * \param[out] data A number of possible collisions.
		 */
		void generateCollisions(const std::vector<RigidBody*>& rigidBodies,
								FixedSizeContainer<CollisionPair>& data) override;

	private:
		/**
		 * \brief Check for collision between two rigid bodies and
		 * generate one if existent.
		 * \param first The first rigid body.
		 * \param second The second rigid body.
		 * \param[out] data This is were newly generated collision
		 * pairs will be put
		 * \return True if there is a potential collision, false
		 * otherwise.
		 */
		bool createBroadPhaseCollision(RigidBody* first,
									   RigidBody* second,
									   FixedSizeContainer<CollisionPair>& data);
	};
}
