#include "R3D/RigidBodyEngine/CollisionDetection/CollisionMask.h"

namespace r3
{
	CollisionMask::CollisionMask(const unsigned layer,
	                             const unsigned group)
		: m_group{group},
		m_layer{layer}
	{
	}

	bool CollisionMask::operator==(const CollisionMask& mask) const
	{
		return m_group == mask.m_group && m_layer == mask.m_layer;
	}

	bool CollisionMask::operator!=(const CollisionMask& mask) const
	{
		return !(*this == mask);
	}
}
