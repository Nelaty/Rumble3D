#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPair.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Interface for intermediate phase filters. These filters
	 * are an optional part of the broad phase. They are executed after
	 * an IBroadPhaseFilter. They are functionally identical to an 
	 * IBroadPhaseFilter, but can be chained.
	 */
	class R3D_EXPORT IIntermediatePhaseFilter
	{
	public:
		virtual ~IIntermediatePhaseFilter() = default;

		/**
		 * \brief Further filter a previous set of collisions, which might
		 * still contain a lot of false negatives.
		 * \param collisions
		 */
		virtual void generateCollisions(FixedSizeContainer<CollisionPair>& collisions) = 0;

	protected:
		explicit IIntermediatePhaseFilter() = default;
	};
}