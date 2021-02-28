#include "R3D/Utility/Random.h"

#include <stdexcept>

namespace r3
{
	void Random::seed()
	{
	    std::random_device rd;
	    seed(rd());
	}

	void Random::seed(const unsigned int seed)
	{
	    s_rng32.seed(seed);
        s_rng64.seed(seed);
        s_seed = seed;
	}

	unsigned int Random::getSeed()
	{
		return s_seed;
	}

	int Random::randomInt()
	{
	    return s_rng32();
	}

	int32_t Random::randomInt(const int32_t min, const int32_t max)
	{
	    if(min > max) throw std::invalid_argument("min value larger than max is not allowed");
		return s_rng32() % (max - min + 1) + min;
	}

	float Random::randomFloat()
	{
		return randomFloatZeroOne() * std::numeric_limits<float>::max();
	}

	float Random::randomFloat(const float min, const float max)
	{
	    if(min > max) throw std::invalid_argument("min value larger than max is not allowed");
		return randomFloatZeroOne() * (max - min) + min;
	}

	float Random::randomFloatZeroOne()
	{
	    return s_distFloatZeroOne(s_rng32);
	}

	double Random::randomDouble()
	{
		return randomDoubleZeroOne() * std::numeric_limits<double>::max();
	}

	double Random::randomDouble(const double min, const double max)
	{
        if(min > max) throw std::invalid_argument("min value larger than max is not allowed");
		return randomDoubleZeroOne() * (max - min) + min;
	}

	double Random::randomDoubleZeroOne()
	{
	    return s_distDoubleZeroOne(s_rng64);
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

	int Random::randomSign(float chance)
	{
		if(randomBool(chance)) return 1;
		else return -1;
	}

    std::mt19937 Random::s_rng32 = std::mt19937();
    std::mt19937_64 Random::s_rng64 = std::mt19937_64();

    std::uniform_int_distribution<int32_t> Random::s_distInt32 =
            std::uniform_int_distribution<int32_t>(std::numeric_limits<int32_t>::min(),
                                                   std::numeric_limits<int32_t>::max());
    std::uniform_int_distribution<int64_t> Random::s_distInt64 =
            std::uniform_int_distribution<int64_t>(std::numeric_limits<int64_t>::min(),
                                                   std::numeric_limits<int64_t>::max());
    std::uniform_real_distribution<float> Random::s_distFloatZeroOne =
            std::uniform_real_distribution<float>(0.0f, 1.0f);
    std::uniform_real_distribution<double> Random::s_distDoubleZeroOne =
            std::uniform_real_distribution<double>(0.0, 1.0);

	unsigned int Random::s_seed = 0;
}
