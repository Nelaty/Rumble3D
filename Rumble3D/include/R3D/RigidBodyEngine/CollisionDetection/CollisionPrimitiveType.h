#pragma once
#include "R3D/Common/Common.h"

namespace r3
{
	enum CollisionPrimitiveType
	{
		R3D_PRIMITIVE_BOX = 0,
		R3D_PRIMITIVE_SPHERE,
		R3D_PRIMITIVE_PLANE,

		R3D_PRIMITIVE_TYPE_COUNT,
		R3D_PRIMITIVE_TYPE_INVALID
	};
}
