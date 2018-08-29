#include "R3D/RigidBodyEngine/CollisionDetection/NarrowPhaseFilter.h"

#include "R3D/RigidBodyEngine/CollisionDetection/BoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/SphereSphereNarrowAlgorithm.h"

#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

#include "R3D/RigidBodyEngine/RigidBody.h"

namespace rum
{
	NarrowPhaseFilter::NarrowPhaseFilter(const unsigned iterations, 
										 const unsigned collisionsMax)
		: m_iterations{iterations},
		m_collisionsMax{collisionsMax}
	{
		init();
	}

	NarrowPhaseFilter::~NarrowPhaseFilter()
	= default;

	const CollisionData& NarrowPhaseFilter::generateCollisionData(
		const std::vector<BroadPhaseCollision>& collisions)
	{
		initCollisionData();

		for(auto& it : collisions)
		{
			generateCollisionData(it.m_first, it.m_second);
		}

		return m_collisionData;
	}

	void NarrowPhaseFilter::setBoxBoxAlgorithm(Algorithm<IBoxBoxNarrowAlgorithm> algorithm)
	{
		m_boxBox = std::move(algorithm);
	}

	void NarrowPhaseFilter::setBoxSphereAlgorithm(Algorithm<IBoxSphereNarrowAlgorithm> algorithm)
	{
		m_boxSphere = std::move(algorithm);
	}

	void NarrowPhaseFilter::setSphereSphereAlgorithm(Algorithm<ISphereSphereNarrowAlgorithm> algorithm)
	{
		m_sphereSphere = std::move(algorithm);
	}

	void NarrowPhaseFilter::init()
	{
		initCollisionData();
		initAlgorithms();
	}

	void NarrowPhaseFilter::initCollisionData()
	{
		m_collisionData.m_contactData.resize(m_collisionsMax);
		m_collisionData.m_contacts = 0;
		m_collisionData.m_contactsMax = m_collisionsMax;
	}

	void NarrowPhaseFilter::initAlgorithms()
	{
		m_boxBox = std::make_unique<BoxBoxNarrowAlgorithm>();
		m_boxSphere = std::make_unique<BoxSphereNarrowAlgorithm>();;
		m_sphereSphere = std::make_unique<SphereSphereNarrowAlgorithm>();;
	}

	void NarrowPhaseFilter::generateCollisionData(RigidBody* first, RigidBody* second)
	{
		auto firstCollisionPrimitive = first->getCollisionPrimitive();
		auto secondCollisionPrimitive = second->getCollisionPrimitive();

		if(!firstCollisionPrimitive || !secondCollisionPrimitive) return;

		firstCollisionPrimitive->generateContact(this, secondCollisionPrimitive);
	}

	void NarrowPhaseFilter::generateCollisionData(CollisionBox* first, CollisionBox* second)
	{
		m_boxBox->generateContactData(first, second, m_collisionData);
	}

	void NarrowPhaseFilter::generateCollisionData(CollisionBox* first, CollisionSphere* second)
	{
		m_boxSphere->generateContactData(first, second, m_collisionData);
	}

	void NarrowPhaseFilter::generateCollisionData(CollisionSphere* first, CollisionSphere* second)
	{
		m_sphereSphere->generateContactData(first, second, m_collisionData);
	}
}
