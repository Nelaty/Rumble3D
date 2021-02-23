#include "R3D/RigidBodyEngine/CollisionCallback.h"

namespace r3
{
	CollisionCallback::CollisionCallback(Callback callback)
	{
		m_callback = callback;
	}

	void CollisionCallback::setCallback(const Callback& callback)
	{
		m_callback = callback;
	}

	void CollisionCallback::execute(RigidBody* rb1, RigidBody* rb2) const
	{
		if(m_callback)
		{
			m_callback(rb1, rb2);
		}
	}
}
