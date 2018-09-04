#pragma once

namespace r3
{
	struct CollisionMask
	{
		explicit CollisionMask(unsigned int layer = 0, unsigned int group = 0);

		bool operator==(const CollisionMask& mask) const;
		bool operator!=(const CollisionMask& mask) const;

		unsigned int m_group;
		unsigned int m_layer;
	};
}