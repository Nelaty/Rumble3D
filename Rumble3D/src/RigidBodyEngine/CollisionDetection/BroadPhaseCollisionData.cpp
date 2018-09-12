#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollisionData.h"
#include <cassert>

namespace r3
{
	BroadPhaseCollisionData::BroadPhaseCollisionData(const int collisionsMax,
													 const int iterations)
	{
		init(collisionsMax, iterations);
	}

	BroadPhaseCollisionData::~BroadPhaseCollisionData()
	= default;

	void BroadPhaseCollisionData::init(const int collisionsMax, const int iterations)
	{
		assert(collisionsMax > 0);

		m_collisionsMax = collisionsMax;
		m_collisions.resize(collisionsMax);
		m_iterations = iterations;

		reset();
	}

	void BroadPhaseCollisionData::reset()
	{
		m_collisionsUsed = 0;
	}

	bool BroadPhaseCollisionData::isFull() const
	{
		return m_collisionsUsed == m_collisionsMax;
	}

	int BroadPhaseCollisionData::getCollisionsLeft() const
	{
		return m_collisionsMax - m_collisionsUsed;
	}

	int BroadPhaseCollisionData::getCollisionsUsed() const
	{
		return m_collisionsUsed;
	}

	int BroadPhaseCollisionData::getSize() const
	{
		return m_collisionsMax;
	}

	CollisionPair* BroadPhaseCollisionData::getAvailableCollision()
	{
		if(isFull()) return nullptr;
		++m_collisionsUsed;
		return &m_collisions[m_collisionsUsed];
	}

	std::vector<CollisionPair>& BroadPhaseCollisionData::getCollisions()
	{
		return m_collisions;
	}

	const std::vector<CollisionPair>& BroadPhaseCollisionData::getCollisions() const
	{
		return m_collisions;
	}
}
