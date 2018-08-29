#include "R3D/Utility/InertiaTensorGenerator.h"

namespace rum
{
	glm::mat3 InertiaTensorGenerator::generateCubeTensor(const real mass, 
												  const real xHalf,
												  const real yHalf,
												  const real zHalf)
	{
		return glm::mat3(
			mass / 48.0f * (yHalf*yHalf + zHalf * zHalf), 0, 0,
			0, mass / 48.0f * (xHalf*xHalf + zHalf * zHalf), 0,
			0, 0, mass / 48.0 * (xHalf*xHalf + yHalf * yHalf));
	}

	glm::mat3 InertiaTensorGenerator::generateSphereTensor(const real mass, 
													const real radius)
	{
		return glm::mat3(
			2.0f * mass * radius * radius / 5.0f, 0, 0,
			0, 2.0f * mass * radius * radius / 5.0f, 0,
			0, 0, 2.0f * mass * radius * radius / 5.0f);
	}

	InertiaTensorGenerator::InertiaTensorGenerator()
	= default;

	InertiaTensorGenerator::~InertiaTensorGenerator()
	= default;
}
