#include "R3D/RigidBodyEngine/CollisionDetection/CollisionDetector.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include "R3D/RigidBodyEngine/CollisionDetection/IBroadPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/IIntermediatePhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseFilter.h"

#include <algorithm>

namespace r3
{
	CollisionDetector::CollisionDetector(const unsigned int contactsMax,
										 const unsigned int iterations)
	{
		init(contactsMax, iterations);
	}

	CollisionDetector::~CollisionDetector()
	= default;

	void CollisionDetector::init(const unsigned contactsMax,
	                             const unsigned iterations)
	{
		m_contactsMax = contactsMax;
		m_iterations = iterations;

		m_broadPhaseCollisions.init(contactsMax, iterations);
		m_collisions.init(contactsMax, iterations);
	}

	void CollisionDetector::reset()
	{
		m_broadPhaseCollisions.reset();
		m_collisions.reset();
	}

	const CollisionData& CollisionDetector::generateCollisions(const std::vector<RigidBody*>& rigidBodies)
	{
		reset();
		if(!m_broadPhaseFilter || !m_narrowPhaseFilter)
		{
			return m_collisions;
		}

		m_broadPhaseFilter->generateCollisions(rigidBodies, m_broadPhaseCollisions);
		for(auto& it : m_intermediatePhaseFilters)
		{
			it->generateCollisions(m_broadPhaseCollisions);
		}
		m_narrowPhaseFilter->generateCollisionData(m_broadPhaseCollisions,
												   m_collisions);
		return m_collisions;
	}

	void CollisionDetector::setBroadPhaseFilter(BroadPhaseFilter_Ptr filter)
	{
		m_broadPhaseFilter = std::move(filter);
	}

	IBroadPhaseFilter* CollisionDetector::getBroadPhaseFilter() const
	{
		return m_broadPhaseFilter.get();
	}

	IIntermediatePhaseFilter* CollisionDetector::addIntermediatePhaseFilter(IntermediatePhaseFilter_Ptr filter)
	{
		m_intermediatePhaseFilters.insert(m_intermediatePhaseFilters.end(),
										  std::move(filter));

		return m_intermediatePhaseFilters.back().get();
	}

	CollisionDetector::IntermediatePhaseFilter_Ptr 
	CollisionDetector::removeIntermediatePhaseFilter(IIntermediatePhaseFilter* filter)
	{
		const auto foundFilter = std::remove_if(m_intermediatePhaseFilters.begin(),
												m_intermediatePhaseFilters.end(),
												[&](const IntermediatePhaseFilter_Ptr& it)
		{
			return it.get() == filter;
		});

		if(foundFilter == m_intermediatePhaseFilters.end())
		{
			return nullptr;
		}

		return std::move(*foundFilter);
	}

	void CollisionDetector::removeAllIntermediatePhaseFilters()
	{
		m_intermediatePhaseFilters.clear();
	}

	void CollisionDetector::setNarrowPhaseFilter(NarrowPhaseFilter_Ptr filter)
	{
		m_narrowPhaseFilter = std::move(filter);
	}

	INarrowPhaseFilter* CollisionDetector::getNarrowPhaseFilter() const
	{
		return m_narrowPhaseFilter.get();
	}
}
