#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Transform3D.h"

namespace r3
{
	class CollisionPrimitive;

	/**
	 * \brief A CollisionObject can collide with other collision objects
	 * in 3D space.
	 */
	class R3D_DECLSPEC CollisionObject
	{
	public:
		virtual ~CollisionObject();

		/**
		 * \brief Set the collision primitive used for collision
		 * detection. 
		 * \param collisionPrimitive The new collision primitive.
		 */
		void setCollisionPrimitive(CollisionPrimitive* collisionPrimitive);
		/** 
		 * \brief Get the currently used collision primitive.
		 * \return The collision primitive.
		 */
		CollisionPrimitive* getCollisionPrimitive() const;

		/**
		 * \brief Get the current transform.
		 * \return The transform.
		 */
		const Transform3D& getTransform() const;
		/**
		 * \brief Get the current transform.
		 * \return The transform.
		 */
		Transform3D& getTransform();

	protected:
		/**
		 * \brief CollisionObject constructor.
		 * \param collisionPrimitive The initial collision primitive.
		 */
		explicit CollisionObject(CollisionPrimitive* collisionPrimitive = nullptr);

		CollisionPrimitive* m_collisionPrimitive;

		Transform3D m_transform;
	};
}
