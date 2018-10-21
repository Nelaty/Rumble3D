#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"
#include "R3D/Utility/FixedSizeContainer.h"

#include "R3D/Common/Common.h"

#include <memory>
#include <list>
#include <vector>

namespace r3
{
	class IBroadPhaseFilter;
	class IIntermediatePhaseFilter;
	class INarrowPhaseFilter;

	class RigidBody;

	/** 
	 * The CollisionDetector acts as a batch controller (batch sequential).
	 * It executes collision detection filters (programs) in a specific
	 * order to generate contacts.
	 */
	class R3D_DECLSPEC CollisionDetector
	{
	public:
		using BroadPhaseFilter_Ptr = std::unique_ptr<IBroadPhaseFilter>;
		using IntermediatePhaseFilter_Ptr = std::unique_ptr<IIntermediatePhaseFilter>;
		using NarrowPhaseFilter_Ptr = std::unique_ptr<INarrowPhaseFilter>;

		explicit CollisionDetector(unsigned int broadPhaseCollisions = 1000000,
								   unsigned int contactsMax = 1000, 
								   unsigned int iterations = 2000);
		CollisionDetector(const CollisionDetector&) = delete;
		~CollisionDetector();

		/** Set the number of used contacts and iterations. */
		void init(unsigned int broadPhaseCollisions = 1000000,
				  unsigned int contactsMax = 1000, 
				  unsigned int iterations = 2000);

		/** Reset previously calculated collisions. */
		void reset();

		/** 
		 * Set the maximal number of collision pairs created in the broad
		 * and intermediate phases.
		 */
		void setBroadPhaseCollisionsMax(int count);
		/** Set the maximal number of contacts created in the narrow phase. */
		void setContactsMax(int count);
		/** Set the maximal number of iterations used. */
		void setIterations(int iterations);

		/** 
		 * Generate a number of contacts for the given rigid bodies
		 * with the help of the current filters.
		 */
		CollisionData& generateCollisions(const std::vector<RigidBody*>& rigidBodies);

		/** Set the broad phase filter */
		void setBroadPhaseFilter(BroadPhaseFilter_Ptr filter);
		/** Get the currently used broad phase filter. */
		IBroadPhaseFilter* getBroadPhaseFilter() const;

		/** 
		 * Add a new intermediate phase filter, which will be executed
		 * after all currently registered intermediate phase filters. 
		 * \return The newly inserted intermediate phase filter.
		 */
		IIntermediatePhaseFilter* addIntermediatePhaseFilter(IntermediatePhaseFilter_Ptr filter);
		/** 
		 * Remove the given filter from the current list of registered
		 * intermediate phase filters.
		 * \return True if the given filter was found and removed, false otherwise.
		 */
		IntermediatePhaseFilter_Ptr removeIntermediatePhaseFilter(IIntermediatePhaseFilter* filter);
		/** 
		 * Clears the list of all currently registered intermediate
		 * phase filters.
		 */
		void removeAllIntermediatePhaseFilters();

		/** Set the narrow phase filter */
		void setNarrowPhaseFilter(NarrowPhaseFilter_Ptr filter);
		/** Get the currently used narrow phase filter */
		INarrowPhaseFilter* getNarrowPhaseFilter() const;

	private:
		unsigned int m_broadPhaseCollisionsMax;
		
		unsigned int m_contactsMax;
		unsigned int m_iterations;

		FixedSizeContainer<CollisionPair> m_broadPhaseCollisions;
		CollisionData m_collisions;

		BroadPhaseFilter_Ptr m_broadPhaseFilter;
		std::list<IntermediatePhaseFilter_Ptr> m_intermediatePhaseFilters;
		NarrowPhaseFilter_Ptr m_narrowPhaseFilter;
	};
}