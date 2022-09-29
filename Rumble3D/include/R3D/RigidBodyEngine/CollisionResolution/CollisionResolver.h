#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionResolution/ICollisionResolverAccess.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace r3
{
	class ICollisionResolutionFilter;

	/**
	 * \brief Default implementation for a collision resolver.
	 */
	class R3D_EXPORT CollisionResolver : public ICollisionResolverAccess
	{
	public:
		using Filter_Ptr = std::shared_ptr<ICollisionResolutionFilter>;

		explicit CollisionResolver();
		virtual ~CollisionResolver() = default;

		void resolveCollisions(FixedSizeContainer<Contact>& collisionData,
							   real timeDelta) override;

		/**
		 * \brief Insert a new filter, which will be executed after all 
		 * already inserted filters.
		 * \param filter The new filter.
		 * \return The new filter.
		 */
		ICollisionResolutionFilter* appendFilter(const Filter_Ptr& filter);


		/** Get the current number of used filters. */
		std::size_t getFilterCount() const;

		/** 
		 * Removes all filters from this collision resolver. 
		 */
		void clear();

	protected:
		std::vector<Filter_Ptr> m_filters;
	};
}