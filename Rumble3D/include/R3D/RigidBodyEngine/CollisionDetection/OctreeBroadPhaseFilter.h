#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/IBroadPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Octree.h"

namespace r3
{
	class R3D_EXPORT OctreeBroadPhaseFilter : public IBroadPhaseFilter
	{
	public:
		explicit OctreeBroadPhaseFilter() = default;
		~OctreeBroadPhaseFilter() = default;

		void generateCollisions(
			const std::vector<RigidBody*>& rigidBodies,
			FixedSizeContainer<CollisionPair>& data) override;

	private:
		void buildOctree(const std::vector<RigidBody*>& rigidBodies);

		Octree m_octree;
	};
}