#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	/**
	 * \brief Interface for collision resolvers. Uses
	 * ICollisionResolutionFilter to resolve given contacts.
	 */
	class R3D_DECLSPEC ICollisionResolverAccess
	{
	public:
		virtual ~ICollisionResolverAccess() = default;

		virtual void resolveCollisions(CollisionData& collisionData,
									   real timeDelta) = 0;

	protected:
		explicit ICollisionResolverAccess() = default;
	};
}
