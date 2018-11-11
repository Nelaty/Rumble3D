#include "R3D/RigidBodyEngine/CollisionResolution/CollisionResolver.h"
#include "R3D/RigidBodyEngine/CollisionResolution/VelocityResolver.h"
#include "R3D/RigidBodyEngine/CollisionResolution/InterpenetrationResolver.h"
#include "R3D/RigidBodyEngine/CollisionResolution/FrictionResolver.h"

#include <utility>

namespace r3
{
	CollisionResolver::~CollisionResolver()
	= default;

	void CollisionResolver::resolveCollisions(CollisionData& collisionData,
	                                          const real timeDelta)
	{
		if(collisionData.isEmpty())
		{
			return;
		}

		collisionData.prepareContacts(timeDelta);
		for(auto& it : m_filters)
		{
			it->resolve(collisionData, timeDelta);
		}
	}

	ICollisionResolutionFilter* CollisionResolver::appendFilter(Filter_Ptr filter)
	{
		m_filters.emplace_back(std::move(filter));
		return m_filters.back().get();
	}

	unsigned CollisionResolver::getFilterCount() const
	{
		return unsigned(m_filters.size());
	}

	void CollisionResolver::clear()
	{
		m_filters.clear();
	}

	CollisionResolver::CollisionResolver()
	{
		appendFilter(std::make_unique<InterpenetrationResolver>());
		appendFilter(std::make_unique<VelocityResolver>());
		appendFilter(std::make_unique<FrictionResolver>());
	}
}