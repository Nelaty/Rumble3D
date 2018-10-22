#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	class RigidBody;

	/**
	 * \brief A CollisionPair describes a potential collision between
	 * two rigid bodies.
	 */
	class R3D_DECLSPEC CollisionPair
	{
	public:
		/**
		 * \brief CollisionPair constructor
		 * \param first First rigid body
		 * \param second Second rigid body
		 */
		explicit CollisionPair(RigidBody* first = nullptr,
							   RigidBody* second = nullptr);
		~CollisionPair();

		/**
		 * \brief Get a rigid body by index.
		 * \param index Either 0 (first body) or 1 (second body)
		 * \return First or second rigid body.
		 */
		RigidBody* operator[](int index) const;

		/**
		 * \brief Initialize the pair with two potentially colliding rigid
		 * bodies.
		 * \param first The first rigid body
		 * \param second The second rigid body
		 */
		void init(RigidBody* first, RigidBody* second);

		/**
		 * \brief Get the first rigid body.
		 * \return The first rigid body
		 */
		RigidBody* getFirst() const;
		/**
		 * \brief Set the first rigid body
		 * \param first A rigid body, which might collide with the
		 * second one.
		 */
		void setFirst(RigidBody* first);

		/**
		 * \brief Get the second rigid body.
		 * \return The second rigid body
		 */
		RigidBody* getSecond() const;
		/**
		 * \brief Set the second rigid body.
		 * \param second A rigid body, which might collide with the
		 * first one.
		 */
		void setSecond(RigidBody* second);

		/**
		 * \brief Swap first and second rigid body.
		 */
		void swapBodies();

	private:
		RigidBody* m_data[2]{};
	};
}