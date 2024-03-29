#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPair.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	class CollisionPair;

	class CollisionBox;
	class CollisionSphere;

	/**
	 * \brief Interface for narrow phase filters.
	 */
	class R3D_EXPORT INarrowPhaseFilter
	{
	public:
		virtual ~INarrowPhaseFilter() = default;

		/**
		 * \brief Generate contacts.
		 * \param broadPhaseData Collision pairs generated in the
		 * broad phase.
		 * \param[out] collisions All newly generated contacts will
		 * be put in here.
		 */
		virtual void generateCollisionData(const FixedSizeContainer<CollisionPair>& broadPhaseData,
                                           FixedSizeContainer<Contact>& collisions) = 0;

	protected:
		explicit INarrowPhaseFilter() = default;
	};
}
