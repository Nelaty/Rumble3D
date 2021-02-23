#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPair.h"

#include <algorithm>
#include <cassert>

namespace r3
{
	CollisionPair::CollisionPair(RigidBody* first, RigidBody* second)
	{
		init(first, second);
	}

	RigidBody* CollisionPair::operator[](const int index) const
	{
		assert(index == 0 || index == 1);
		return m_data[index];
	}

	void CollisionPair::init(RigidBody* first, RigidBody* second)
	{
		m_data[0] = first;
		m_data[1] = second;
	}

	RigidBody* CollisionPair::getFirst() const
	{
		return m_data[0];
	}

	RigidBody* CollisionPair::getSecond() const
	{
		return m_data[1];
	}

	void CollisionPair::setFirst(RigidBody* first)
	{
		m_data[0] = first;
	}

	void CollisionPair::setSecond(RigidBody* second)
	{
		m_data[1] = second;
	}

	void CollisionPair::swapBodies()
	{
		std::swap(m_data[0], m_data[1]);
	}
}
