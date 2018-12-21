#include "R3D/RigidBodyEngine/CollisionDetection/OctreeBroadPhaseFilter.h"

namespace r3
{
	OctreeBroadPhaseFilter::OctreeBroadPhaseFilter()
	= default;

	OctreeBroadPhaseFilter::~OctreeBroadPhaseFilter()
	= default;

	void OctreeBroadPhaseFilter::generateCollisions(
		const std::vector<RigidBody*>& rigidBodies,
		FixedSizeContainer<CollisionPair>& data)
	{
		buildOctree(rigidBodies);
	}

	void OctreeBroadPhaseFilter::buildOctree(
		const std::vector<RigidBody*>& rigidBodies)
	{
		m_octree = Octree();

		for(auto& it : rigidBodies)
		{
			m_octree.insert(it);
		}
	}
}
