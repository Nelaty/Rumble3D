#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrix.h"

#include <vector>
#include <memory>

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC NarrowPhaseFilter : public INarrowPhaseFilter
	{
	public:
		template<class AlgorithmType>
		using Algorithm = std::unique_ptr<AlgorithmType>;

		explicit NarrowPhaseFilter(unsigned int iterations = 10, unsigned int collisionsMax = 1000);
		~NarrowPhaseFilter();

		void generateCollisionData(const BroadPhaseCollisionData& broadPhaseData,
								   CollisionData& collisions) override;

		/** Generate collisions between two rigid bodies. */
		void generateCollisionData(RigidBody* first, RigidBody* second, CollisionData& collisions);


	protected:
		void init();

		CollisionAlgorithmMatrix m_algorithms;
	};
}
