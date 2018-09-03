#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	class CollisionPrimitive;

	class R3D_DECLSPEC CollisionObject
	{
	public:
		virtual ~CollisionObject();

		/** Set the collision primitive used for collision detection. */
		void setCollisionPrimitive(CollisionPrimitive* collisionPrimitive);
		/** Get the currently used collision primitive */
		CollisionPrimitive* getCollisionPrimitive() const;

	protected:
		explicit CollisionObject(CollisionPrimitive* collisionPrimitive = nullptr);

		CollisionPrimitive* m_collisionPrimitive;
	};
}