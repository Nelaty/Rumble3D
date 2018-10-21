#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseFilter.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	BroadPhaseFilter::BroadPhaseFilter()
		= default;

	BroadPhaseFilter::~BroadPhaseFilter()
		= default;

	void BroadPhaseFilter::generateCollisions(const std::vector<RigidBody*>& rigidBodies,
											  BroadPhaseCollisionData& data)
	{
		/// \todo use rigid body mask and layout
		for(auto i = 0; i < rigidBodies.size(); ++i)
		{
			auto* first = rigidBodies[i];
			for(auto j = i + 1; j < rigidBodies.size(); ++j)
			{
				auto* second = rigidBodies[j];
				if(!createBroadPhaseCollision(first, second, data))
				{
					return;
				}
			}
		}
	}

	bool BroadPhaseFilter::createBroadPhaseCollision(RigidBody* first,
													 RigidBody* second,
													 BroadPhaseCollisionData& data)
	{
		if(!first->hasFiniteMass() && !second->hasFiniteMass())
		{
			return true;
		}
		if(data.isFull())
		{
			return false;
		}

		auto* collision = data.getAvailableCollision();
		if(collision != nullptr)
		{
			collision->init(first, second);
			return true;
		}
	}
}
