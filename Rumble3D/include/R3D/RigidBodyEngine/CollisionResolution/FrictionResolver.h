#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionResolution/ICollisionResolutionFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Specialized collision resolution filter, which adds
	 * friction at given contacts.
	 */
	class R3D_DECLSPEC FrictionResolver : public ICollisionResolutionFilter
	{
	public:
		explicit FrictionResolver() = default;
		~FrictionResolver() = default;


		void resolve(FixedSizeContainer<Contact>& collisionData,
					 real timeDelta) override;
	};
}