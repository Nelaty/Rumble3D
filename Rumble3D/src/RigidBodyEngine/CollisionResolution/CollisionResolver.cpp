#include "R3D/RigidBodyEngine/CollisionResolution/CollisionResolver.h"
#include "R3D/RigidBodyEngine/CollisionResolution/VelocityResolver.h"
#include "R3D/RigidBodyEngine/CollisionResolution/InterpenetrationResolver.h"
#include "R3D/RigidBodyEngine/CollisionResolution/FrictionResolver.h"

#include <utility>

namespace r3
{
	void CollisionResolver::resolveCollisions(FixedSizeContainer<Contact>& collisionData,
	                                          const real timeDelta)
	{
		if(collisionData.isEmpty()) return;

		// \todo: this is a function
		for(auto& it : collisionData.getData())
        {
		    it.calculateInternals(timeDelta);
        }

		for(auto& it : m_filters)
		{
			it->resolve(collisionData, timeDelta);
		}
	}

	ICollisionResolutionFilter* CollisionResolver::appendFilter(const Filter_Ptr& filter)
	{
		m_filters.emplace_back(filter);
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
		appendFilter(std::make_shared<InterpenetrationResolver>());
		appendFilter(std::make_shared<VelocityResolver>());
		appendFilter(std::make_shared<FrictionResolver>());
	}
}