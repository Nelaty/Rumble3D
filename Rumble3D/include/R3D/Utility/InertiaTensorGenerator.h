#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class R3D_DECLSPEC InertiaTensorGenerator
	{
	public:
		static glm::mat3 generateCubeTensor(real mass, real xHalf, real yHalf, real zHalf);
		static glm::mat3 generateSphereTensor(real mass, real radius);

	private:
		InertiaTensorGenerator();
		~InertiaTensorGenerator();
	};
}
