#include "R3D/Utility/InertiaTensorGenerator.h"

namespace r3
{
	glm::mat3 InertiaTensorGenerator::generateCubeTensor(const real mass,
														 const real xHalf,
														 const real yHalf,
														 const real zHalf)
	{
		//auto scalar = mass / real(48);
		// Millington definition
		auto scalar = real(0.3) * mass;
		//auto scalar = mass / real(12);

		const auto x = xHalf * xHalf;
		const auto y = yHalf * yHalf;
		const auto z = zHalf * zHalf;

		return glm::mat3(
			scalar * (y + z), 0, 0,
			0, scalar * (x + z), 0,
			0, 0, scalar * (x + y));
	}

	glm::mat3 InertiaTensorGenerator::generateSphereTensor(const real mass, 
													const real radius)
	{
		// Inertia tensor for a solid sphere
		// https://en.wikipedia.org/wiki/List_of_moments_of_inertia
		const auto scalar = real(2) * mass * radius * radius / real(5);
		return glm::mat3(scalar, 0, 0,
						 0, scalar, 0,
						 0, 0, scalar);
	}
}
