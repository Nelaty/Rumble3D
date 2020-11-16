#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionResolution/ICollisionResolutionFilter.h"

namespace r3
{
	/**
	 * \brief Specialized collision resolution filter, which adds
	 * friction at given contacts.
	 */
	class R3D_DECLSPEC FrictionResolver : public ICollisionResolutionFilter
	{
	public:
		explicit FrictionResolver();
		~FrictionResolver();


		void resolve(CollisionData& collisionData,
					 real timeDelta) override;
	};
}