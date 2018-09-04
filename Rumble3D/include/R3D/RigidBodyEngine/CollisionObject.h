#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Transform3D.h"

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

		const Transform3D& getTransform() const;
		Transform3D& getTransform();

	protected:
		explicit CollisionObject(CollisionPrimitive* collisionPrimitive = nullptr);

		CollisionPrimitive* m_collisionPrimitive;

		Transform3D m_transform;
	};
}
