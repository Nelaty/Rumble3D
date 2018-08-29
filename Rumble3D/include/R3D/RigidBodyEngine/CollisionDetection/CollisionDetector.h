#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

#include <memory>
#include <list>
#include <vector>

namespace rum
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
	class CollisionDetector
	{
	public:
		using BroadPhaseFilter_Ptr = std::unique_ptr<IBroadPhaseFilter>;
		using IntermediatePhaseFilter_Ptr = std::unique_ptr<IIntermediatePhaseFilter>;
		using NarrowPhaseFilter_Ptr = std::unique_ptr<INarrowPhaseFilter>;

		explicit CollisionDetector(unsigned int iterations = 10, unsigned int contactsMax = 1000);
		CollisionDetector(const CollisionDetector&) = delete;
		~CollisionDetector();

		/** 
		 * Generate a number of contacts for the given rigid bodies
		 * with the help of the current filters.
		 */
		const CollisionData& generateCollisions(const std::vector<RigidBody*>& rigidBodies);

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
		unsigned int m_contactsMax;
		unsigned int m_iterations;

		BroadPhaseFilter_Ptr m_broadPhaseFilter;
		std::list<IntermediatePhaseFilter_Ptr> m_intermediatePhaseFilters;
		NarrowPhaseFilter_Ptr m_narrowPhaseFilter;
	};
}