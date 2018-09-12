#pragma once
#include "R3D/Common/Common.h"
#include "CollisionPair.h"

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC Contact
	{
	public:
		explicit Contact();
		~Contact();

		/** Get the first colliding rigid body. */
		RigidBody* getFirst() const;
		/** Get the second colliding rigid body. */
		RigidBody* getSecond() const;

	private:
		CollisionPair m_pair;
	};
}
