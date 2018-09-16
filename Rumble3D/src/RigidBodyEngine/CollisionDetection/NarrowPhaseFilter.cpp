#include "R3D/RigidBodyEngine/CollisionDetection/NarrowPhaseFilter.h"
#include "R3D/ServiceLocator/ServiceLocatorCollisionAlgorithmMatrix.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"

#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	NarrowPhaseFilter::NarrowPhaseFilter(const unsigned iterations, 
										 const unsigned collisionsMax)
	{
		init();
	}

	NarrowPhaseFilter::~NarrowPhaseFilter()
	= default;

	void NarrowPhaseFilter::generateCollisionData(const BroadPhaseCollisionData& broadPhaseData,
												  CollisionData& collisions)
	{
		const auto& data = broadPhaseData.getCollisions();
		for(auto& it : data)
		{
			generateCollisionData(it.m_first, it.m_second, collisions);
		}
	}

	void NarrowPhaseFilter::init()
	{
		m_algorithms = ServiceLocatorCollisionAlgorithmMatrix::getMatrix();
	}

	void NarrowPhaseFilter::generateCollisionData(RigidBody* first, RigidBody* second, CollisionData& collisions)
	{
		const auto firstCollider = first->getCollisionPrimitive();
		const auto secondCollider = second->getCollisionPrimitive();

		if(!firstCollider || !secondCollider) return;

		auto algorithm = m_algorithms.getAlgorithm(firstCollider->getType(),
												   secondCollider->getType());

		algorithm->generateContactData(first, second, collisions);
	}
}
