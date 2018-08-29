#pragma once
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class InertiaTensorGenerator
	{
	public:
		static glm::mat3 generateCubeTensor(real mass, real xHalf, real yHalf, real zHalf);
		static glm::mat3 generateSphereTensor(real mass, real radius);

	private:
		InertiaTensorGenerator();
		~InertiaTensorGenerator();
	};
}
