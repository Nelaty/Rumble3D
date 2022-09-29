#pragma once
#include "R3D/Common/Common.h"

#include <glm/glm.hpp>
#include <climits>
#include <random>

namespace r3
{
	/**
	* \brief Equally distributed random number generator.
	*/
	class R3D_EXPORT Random
	{
	public:
		/**
		 * \brief Seed the random number generator with the current time.
		 */
		static void seed();
		/**
		 * \brief Seed the random number generator with a given seed.
		 * \brief seed The number used as a seed
		 */
		static void seed(unsigned int seed);
		/**
		 * \brief Get the seed, with which the random number generator
		 * got initialized.
		 * \return The seed
		 */
		static unsigned int getSeed();
        /**
		 * \brief Calculate random integer value \f$\in\f$ [INT_MIN, INT_MAX].
		 * \return A random integer
		 */
		static int randomInt();
		/**
		 * \brief Calculate random integer value in a user defined range.
		 * \param min Minimal value
		 * \param max Maximal value
		 * \return A random integer
		 */
		static int32_t randomInt(int min32_t, int max32_t);

		/**
		 * \brief Calculate random float value \f$\in\f$ [FLOAT_MIN, FLOAT_MAX].
		 * \return A random float
		 */
		static float randomFloat();
		/**
		 * \brief Calculate random float value in a user defined range.
		 * \param min Minimal value
		 * \param max Maximal value
		 * \return A random float
		 *
		 */
		static float randomFloat(float min, float max);
		/**
		 * \brief Calculate random float value \f$\in\f$ [0.0f, 1.0f].
		 * \return A random float
		 */
		static float randomFloatZeroOne();

		/**
		 * \brief Calculate random double value \f$\in\f$ [DOUBLE_MIN, DOUBLE_MAX].
		 * \return A random double
		 */
		static double randomDouble();
		/**
		 * \brief Calculate random double value in a user defined range.
		 * \param min Minimal value
		 * \param max Maximal value
		 * \return A random double
		 */
		static double randomDouble(double min, double max);
		/**
		 * \brief Calculate random double value \f$\in\f$ [0.0f, 1.0f].
		 * \return A random double
		 */
		static double randomDoubleZeroOne();

		/**
		 * \brief Calculate a random 2D vector.
		 * \return A random 2D vector
		 */
		static glm::vec2 randomVec2();
		/**
		 * \brief Calculate a random 2D vector in a user defined range.
		 * \param min Minimal value for a vector component
		 * \param max Maximal value for a vector component
		 * \return A random 2D vector
		 */
		static glm::vec2 randomVec2(float min, float max);
		/**
		 * \brief Calculate a random 2D vector in a user defined range.
		 * \param min Minimal value
		 * \param max Maximal value
		 * \return A random 2D vector
		 */
		static glm::vec2 randomVec2(const glm::vec2& min,
									const glm::vec2& max);

		/**
		 * \brief Calculate a random 3D vector.
		 * \return A random 3D vector
		 */
		static glm::vec3 randomVec3();
		/**
		 * \brief Calculate a random 3D vector in a user defined range.
		 * \param min Minimal value for a vector component
		 * \param max Maximal value for a vector component
		 * \return A random 3D vector
		 */
		static glm::vec3 randomVec3(float min, float max);
		/**
		 * \brief Calculate a random 3D vector in a user defined range.
		 * \param min Minimal value
		 * \param max Maximal value
		 * \return A random 3D vector
		 */
		static glm::vec3 randomVec3(const glm::vec3& min,
									const glm::vec3& max);

		/**
		 * \brief Calculate a random 4D vector.
		 * \return A random 4D vector
		 */
		static glm::vec4 randomVec4();
		/**
		 * \brief Calculate a random 4D vector in a user defined range.
		 * \param min Minimal value for a vector component
		 * \param max Maximal value for a vector component
		 * \return A random 4D vector
		 */
		static glm::vec4 randomVec4(float min, float max);
		/**
		 * \brief Calculate a random 4D vector in a user defined range.
		 * \param min Minimal value
		 * \param max Maximal value
		 * \return A random 4D vector
		 */
		static glm::vec4 randomVec4(const glm::vec4& min,
									const glm::vec4& max);

		/**
		 * \brief Get a random boolean value.
		 * \param chance The probability of the boolean value to be true.
		 * \return A random bool
		 */
		static bool randomBool(float chance = 0.5f);

		/**
		 * \brief Get a positive signed value of 1 with a given chance
		 * \param chance The probability of returning a positive value
		 * \return 1 or -1
		 */
		static int randomSign(float chance = 0.5f);

	private:
		explicit Random() = default;
		~Random() = default;

		static std::mt19937 s_rng32;
        static std::mt19937_64 s_rng64;
        static std::uniform_int_distribution<int32_t> s_distInt32;
        static std::uniform_int_distribution<int64_t> s_distInt64;
        static std::uniform_real_distribution<float> s_distFloatZeroOne;
        static std::uniform_real_distribution<double> s_distDoubleZeroOne;
        static unsigned int s_seed;
	};
}
