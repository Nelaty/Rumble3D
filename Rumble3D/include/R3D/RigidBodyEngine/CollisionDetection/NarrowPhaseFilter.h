#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

#include <vector>
#include <memory>

namespace rum
{
	class IBoxBoxNarrowAlgorithm;
	class IBoxSphereNarrowAlgorithm;
	class ISphereSphereNarrowAlgorithm;

	class RigidBody;
	class CollisionBox;
	class CollisionSphere;

	class NarrowPhaseFilter : public INarrowPhaseFilter
	{
	public:
		template<class AlgorithmType>
		using Algorithm = std::unique_ptr<AlgorithmType>;

		explicit NarrowPhaseFilter(unsigned int iterations = 10, unsigned int collisionsMax = 1000);
		~NarrowPhaseFilter();

		const CollisionData& generateCollisionData(
			const std::vector<BroadPhaseCollision>& collisions) override;

		/** Set the algorithm used for box-box collisions. */
		void setBoxBoxAlgorithm(Algorithm<IBoxBoxNarrowAlgorithm> algorithm);
		/** Set the algorithm used for box-sphere collisions. */
		void setBoxSphereAlgorithm(Algorithm<IBoxSphereNarrowAlgorithm> algorithm);
		/** Set the algorithm used for sphere-sphere collisions. */
		void setSphereSphereAlgorithm(Algorithm<ISphereSphereNarrowAlgorithm> algorithm);



		void generateCollisionData(RigidBody* first, RigidBody* second);
		void generateCollisionData(CollisionBox* first, CollisionBox* second) override;
		void generateCollisionData(CollisionBox* first, CollisionSphere* second) override;
		void generateCollisionData(CollisionSphere* first, CollisionSphere* second) override;


	protected:
		void init();
		void initCollisionData();
		void initAlgorithms();

		unsigned int m_iterations;
		unsigned int m_collisionsMax;

		CollisionData m_collisionData;

		Algorithm<IBoxBoxNarrowAlgorithm> m_boxBox;
		Algorithm<IBoxSphereNarrowAlgorithm> m_boxSphere;
		Algorithm<ISphereSphereNarrowAlgorithm> m_sphereSphere;
	};
}
