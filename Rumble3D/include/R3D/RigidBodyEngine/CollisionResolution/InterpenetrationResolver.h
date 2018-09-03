#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionResolution/ICollisionResolutionFilter.h"

namespace r3
{
	class R3D_DECLSPEC InterpenetrationResolver : public ICollisionResolutionFilter
	{
	public:
		explicit InterpenetrationResolver();
		~InterpenetrationResolver();

		void resolve(const CollisionData& collisionData) override;
	};
}