#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	struct R3D_DECLSPEC CollisionMask
	{
		explicit CollisionMask(unsigned int layer = 0, unsigned int group = 0);

		bool operator==(const CollisionMask& mask) const;
		bool operator!=(const CollisionMask& mask) const;

		unsigned int m_group;
		unsigned int m_layer;
	};
}