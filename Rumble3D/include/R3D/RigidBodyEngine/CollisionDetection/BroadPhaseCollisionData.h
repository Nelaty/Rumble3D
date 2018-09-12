#pragma once
#include "CollisionPair.h"

#include <vector>

namespace r3
{
	class BroadPhaseCollisionData
	{
	public:
		explicit BroadPhaseCollisionData(int collisionsMax = 1000, int iterations = 0);
		~BroadPhaseCollisionData();

		/** Set the maximal number of used collisions. */
		void init(int collisionsMax, int iterations);
		/** Reset the number of used collisions. */
		void reset();
		
		/** Check if there is no more room for new contacts. */
		bool isFull() const;

		/** Check how many collision pairs can still be inserted. */
		int getCollisionsLeft() const;
		/** Check how many collision pairs have been inserted. */
		int getCollisionsUsed() const;
		/** Get the maximal number of collisions. */
		int getSize() const;

		/** Get the next available collision. Automatically uses it! */
		CollisionPair* getAvailableCollision();
		/** Get all collision pairs (even collisions that are not in use!) */
		std::vector<CollisionPair>& getCollisions();
		/** Get all collision pairs (even collisions that are not in use!) */
		const std::vector<CollisionPair>& getCollisions() const;

	private:
		std::vector<CollisionPair> m_collisions;
		int m_collisionsMax{};
		int m_collisionsUsed{};
		int m_iterations{};
	};
}