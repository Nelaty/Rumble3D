#pragma once
#include <glm/glm.hpp>

namespace utl
{
	/**
	* Equally distributed random number generator.
	*/
	class Random
	{
	public:
		/** Seed the random number generator with the current time. */
		static void seed();
		/** Seed the random number generator with a given seed. */
		static void seed(unsigned int seed);
		static unsigned int getSeed();

		/** Calculate random integer value. */
		static int randomInt();
		static int randomInt(int min, int max);
			
		/** Calculate random float value. */
		static float randomFloat();
		static float randomFloat(float min, float max);
		static float randomFloatZeroOne();

		/** Calculate random double value. */
		static double randomDouble();
		static double randomDouble(double min, double max);
		static double randomDoubleZeroOne();

		/** Calculate a random 2D vector. */
		static glm::vec2 randomVec2();
		/** Calculate a random 2D vector. */
		static glm::vec2 randomVec2(float min, float max);

		/** Calculate a random 3D vector. */
		static glm::vec3 randomVec3();
		/** Calculate a random 3D vector. */
		static glm::vec3 randomVec3(float min, float max);

		/** Calculate a random 4D vector. */
		static glm::vec4 randomVec4();
		/** Calculate a random 4D vector. */
		static glm::vec4 randomVec4(float min, float max);

		/** 
		 * Get a random boolean value. 
		 * \param chance The probability of the boolean value to be true.
		 */
		static bool randomBool(float chance);

	private:
		explicit Random();
		~Random();

		static unsigned int s_seed;
	};
}
