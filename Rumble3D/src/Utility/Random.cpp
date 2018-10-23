#include "R3D/Utility/Random.h"
#include <cassert>
#include <utility>
#include <ctime>

namespace r3
{
	void Random::seed()
	{
		seed(time(nullptr));
	}

	void Random::seed(const unsigned int seed)
	{
		s_seed = seed;
		srand(seed);
	}

	unsigned int Random::getSeed()
	{
		return s_seed;
	}

	int Random::randomInt()
	{
		return rand();
	}

	int Random::randomInt(const int min, const int max)
	{
		assert(min <= max);
		return rand() % (max - min) + min;
	}

	float Random::randomFloat()
	{
		return randomFloatZeroOne() * FLT_MAX;
	}

	float Random::randomFloat(const float min, const float max)
	{
		assert(min <= max);
		return randomFloatZeroOne() * (max - min) + min;
	}

	float Random::randomFloatZeroOne()
	{
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	}

	double Random::randomDouble()
	{
		return randomDoubleZeroOne() * DBL_MAX;
	}

	double Random::randomDouble(const double min, const double max)
	{
		assert(min <= max);
		return randomDoubleZeroOne() * (max - min) + min;
	}

	double Random::randomDoubleZeroOne()
	{
		return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	}

	glm::vec2 Random::randomVec2()
	{
		return glm::vec2(randomFloat(),
						 randomFloat());
	}

	glm::vec2 Random::randomVec2(const float min, const float max)
	{
		return glm::vec2(randomFloat(min, max),
						 randomFloat(min, max));
	}

	glm::vec2 Random::randomVec2(const glm::vec2& min, const glm::vec2& max)
	{
		return glm::vec2(randomFloat(min.x, max.x),
						 randomFloat(min.y, max.y));
	}

	glm::vec3 Random::randomVec3()
	{
		return glm::vec3(randomFloat(),
						 randomFloat(),
						 randomFloat());
	}

	glm::vec3 Random::randomVec3(const float min, const float max)
	{
		return glm::vec3(randomFloat(min, max),
						 randomFloat(min, max),
						 randomFloat(min, max));
	}

	glm::vec3 Random::randomVec3(const glm::vec3& min, const glm::vec3& max)
	{
		return glm::vec3(randomFloat(min.x, max.x),
						 randomFloat(min.y, max.y),
						 randomFloat(min.z, max.z));
	}

	glm::vec4 Random::randomVec4()
	{
		return glm::vec4(randomFloat(),
						 randomFloat(),
						 randomFloat(),
						 randomFloat());
	}

	glm::vec4 Random::randomVec4(const float min, const float max)
	{
		return glm::vec4(randomFloat(min, max),
						 randomFloat(min, max),
						 randomFloat(min, max),
						 randomFloat(min, max));
	}

	glm::vec4 Random::randomVec4(const glm::vec4& min, const glm::vec4& max)
	{
		return glm::vec4(randomFloat(min.x, max.x),
						 randomFloat(min.y, max.y),
						 randomFloat(min.z, max.z),
						 randomFloat(min.w, max.w));
	}

	bool Random::randomBool(const float chance)
	{
		return randomFloatZeroOne() < chance;
	}

	Random::Random()
		= default;

	Random::~Random()
		= default;

	unsigned int Random::s_seed = 0;
}
