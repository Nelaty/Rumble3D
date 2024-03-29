#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrix.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

#include <memory>

namespace r3
{
	class RigidBody;

	class R3D_EXPORT NarrowPhaseFilter : public INarrowPhaseFilter
	{
	public:
		template<class AlgorithmType>
		using Algorithm = std::unique_ptr<AlgorithmType>;

		explicit NarrowPhaseFilter(unsigned iterations = 10, unsigned collisionsMax = 1000);
		~NarrowPhaseFilter() = default;

		/**
		 * \brief Generate contacts.
		 * \param broadPhaseData Collision pairs generated in the
		 * broad phase.
		 * \param[out] collisions All newly generated contacts will
		 * be put in here.
		 */
		void generateCollisionData(const FixedSizeContainer<CollisionPair>& broadPhaseData,
                                   FixedSizeContainer<Contact>& collisions) override;

		/** 
		 * \brief Generate contacts between two rigid bodies if existent. 
		 * \param first The first participating rigid body.
		 * \param second The second participating rigid body.
		 * \param[out] collisions All newly generated contacts will
		 * be put in here.
		 */
		void generateCollisionData(RigidBody* first,
								   RigidBody* second,
                                   FixedSizeContainer<Contact>& collisions);


	protected:
		/**
		 * \brief Initialize the algorithm matrix.
		 */
		void init();

		CollisionAlgorithmMatrix m_algorithms;
	};
}
