#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	/**
	 * \brief Interface for collision resolution filter.
	 */
	class R3D_DECLSPEC ICollisionResolutionFilter
	{
	public:
		virtual ~ICollisionResolutionFilter();

		/**
		 * \brief Resolve given contacts.
		 * \param collisionData The contacts to resolve.
		 * \param timeDelta The time step of the current physics
		 * update.
		 */
		virtual void resolve(CollisionData& collisionData,
							 real timeDelta) = 0;

	protected:
		explicit ICollisionResolutionFilter();
	};
}