#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	/**
	 * \brief Used to group rigid bodies. Only rigid bodies from the
	 * same layer can collide. Rigid bodies from the same group cannot
	 * collide!
	 */
	struct R3D_DECLSPEC CollisionMask
	{
		/**
		 * \brief CollisionMask constructor
		 * \param layer Only bodies from the same layer can collide.
		 * \param group Bodies from the same group can't collide.
		 */
		explicit CollisionMask(unsigned int layer = 0, unsigned int group = 0);

		bool operator==(const CollisionMask& mask) const;
		bool operator!=(const CollisionMask& mask) const;

		unsigned int m_group;
		unsigned int m_layer;
	};
}