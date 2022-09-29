#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

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
	class R3D_EXPORT CollisionDetector
	{
	public:
		using BroadPhaseFilter_Ptr = std::unique_ptr<IBroadPhaseFilter>;
		using IntermediatePhaseFilter_Ptr = std::unique_ptr<IIntermediatePhaseFilter>;
		using NarrowPhaseFilter_Ptr = std::unique_ptr<INarrowPhaseFilter>;

		/**
		 * \brief CollisionDetector constructor.
		 * \param broadPhaseCollisions The maximal number of collision
		 * that can be generated in the broad phase.
		 * \param contactsMax The maximal number of contacts that can
		 * be generated in the narrow phase.
		 * \param iterations The maximal number of iterations that can
		 * be used in contact generation.
		 */
		explicit CollisionDetector(unsigned broadPhaseCollisions = 1000000,
								   unsigned contactsMax = 1000, 
								   unsigned iterations = 2000);
		CollisionDetector(const CollisionDetector&) = delete;
		~CollisionDetector();

		/** 
		 * \brief Set the number of used contacts and iterations. 
		 * \param broadPhaseCollisions The maximal number of collision
		 * that can be generated in the broad phase.
		 * \param contactsMax The maximal number of contacts that can
		 * be generated in the narrow phase.
		 * \param iterations The maximal number of iterations that can
		 * be used in contact generation.
		 */
		void init(unsigned broadPhaseCollisions = 1000000,
				  unsigned contactsMax = 1000, 
				  unsigned iterations = 2000);

		/**
		 * \brief Reset previously calculated collisions.
		 */
		void reset();

		/** 
		 * \brief Set the maximal number of collision pairs created in the broad
		 * and intermediate phases.
		 * \param count The maximal number of collision pairs that can
		 * be generated in the broad phase.
		 */
		void setBroadPhaseCollisionsMax(int count);
		/** 
		 * \brief Set the maximal number of contacts created in the narrow phase. 
		 * \param count The maximal number of contacts.
		 */
		void setContactsMax(int count);
		/**
		 * \brief Set the maximal number of iterations used.
		 * \param iterations The maximal number of iterations.
		 */
		void setIterations(int iterations);

		/** 
		 * \brief Generate a number of contacts for the given rigid bodies
		 * with the help of the current filters.
		 * \param rigidBodies The rigid bodies used for contact generation.
		 * \return The generated contacts.
		 */
        FixedSizeContainer<Contact>& generateCollisions(const std::vector<RigidBody*>& rigidBodies);

		/**
		 * \brief Set the currently used broad phase filter 
		 * \param filter The broad phase filter.
		 */
		void setBroadPhaseFilter(BroadPhaseFilter_Ptr filter);
		/** 
		 * \brief Get the currently used broad phase filter. 
		 * \return The broad phase filter.
		 */
		IBroadPhaseFilter* getBroadPhaseFilter() const;

		/** 
		 * \brief Add a new intermediate phase filter, which will be executed
		 * after all currently registered intermediate phase filters. 
		 * \param filter The new intermediate phase filter
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
		 * \brief Clears the list of all currently registered intermediate
		 * phase filters.
		 */
		void removeAllIntermediatePhaseFilters();

		/** 
		 * \brief Set the currently used narrow phase filter. 
		 * \param filter The new narrow phase filter.
		 */
		void setNarrowPhaseFilter(NarrowPhaseFilter_Ptr filter);
		/** 
		 * \brief Get the currently used narrow phase filter.
		 * \return The narrow phase filter.
		 */
		INarrowPhaseFilter* getNarrowPhaseFilter() const;

	private:
		unsigned int m_broadPhaseCollisionsMax;
		
		unsigned int m_contactsMax;
		unsigned int m_iterations;

		FixedSizeContainer<CollisionPair> m_broadPhaseCollisions;
        FixedSizeContainer<Contact> m_collisions;

		BroadPhaseFilter_Ptr m_broadPhaseFilter;
		std::list<IntermediatePhaseFilter_Ptr> m_intermediatePhaseFilters;
		NarrowPhaseFilter_Ptr m_narrowPhaseFilter;
	};
}