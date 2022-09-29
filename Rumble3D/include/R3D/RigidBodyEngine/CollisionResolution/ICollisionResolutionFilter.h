#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Interface for collision resolution filter.
	 */
	class R3D_EXPORT ICollisionResolutionFilter
	{
	public:
		virtual ~ICollisionResolutionFilter() = default;

		/**
		 * \brief Resolve given contacts.
		 * \param collisionData The contacts to resolve.
		 * \param timeDelta The time step of the current physics
		 * update.
		 */
		virtual void resolve(FixedSizeContainer<Contact>& collisionData,
							 real timeDelta) = 0;

	protected:
		explicit ICollisionResolutionFilter() = default;
	};
}