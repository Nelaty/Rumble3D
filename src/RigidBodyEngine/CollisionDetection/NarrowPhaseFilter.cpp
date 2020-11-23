#include "R3D/RigidBodyEngine/CollisionDetection/NarrowPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrixFactory.h"
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

	void NarrowPhaseFilter::generateCollisionData(const FixedSizeContainer<CollisionPair>& broadPhaseData,
												  CollisionData& collisions)
	{
		const auto& data = broadPhaseData.getData();
		for(auto i = 0; i < broadPhaseData.getEntriesUsed(); ++i)
		{
			generateCollisionData(data[i].getFirst(), data[i].getSecond(), collisions);
		}
	}

	void NarrowPhaseFilter::init()
	{
		m_algorithms = CollisionAlgorithmMatrixFactory::getMatrix();
	}

	void NarrowPhaseFilter::generateCollisionData(RigidBody* first, RigidBody* second, CollisionData& collisions)
	{
		const auto firstCollider = first->getCollisionPrimitive();
		const auto secondCollider = second->getCollisionPrimitive();

		if(!firstCollider || !secondCollider) return;

		auto algorithm = m_algorithms.getAlgorithm(firstCollider->getType(),
												   secondCollider->getType());

		/// \todo: replace CollisionData structure with FixedSizeContainer
		if(algorithm->generateContactData(first, second, collisions))
		{	
			first->getCollisionCallback().execute(first, second);
			second->getCollisionCallback().execute(first, second);
		}
	}
}
