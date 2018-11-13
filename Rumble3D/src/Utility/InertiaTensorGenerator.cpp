#include "R3D/Utility/InertiaTensorGenerator.h"

namespace r3
{
	glm::mat3 InertiaTensorGenerator::generateCubeTensor(const real mass,
														 const real xHalf,
														 const real yHalf,
														 const real zHalf)
	{
		auto scalar = mass / static_cast<real>(48.0f);
		scalar = real(0.3) * mass;

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
		const auto scalar = static_cast<real>(2.0f) * mass * mass * radius / static_cast<real>(5.0f);
		return glm::mat3(scalar, 0, 0,
						 0, scalar, 0,
						 0, 0, scalar);
	}

	InertiaTensorGenerator::InertiaTensorGenerator()
	= default;

	InertiaTensorGenerator::~InertiaTensorGenerator()
	= default;
}
