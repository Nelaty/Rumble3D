#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	/**
	 * \brief Static class, which provides methods to generate inertia
	 * tensors for various shapes.
	 */
	class R3D_EXPORT InertiaTensorGenerator
	{
	public:
		/**
		 * \brief Generate an inertia tensor for a box shape.
		 * \param mass The mass of the object.
		 * \param xHalf Half length of the x side.
		 * \param yHalf Half length of the y side.
		 * \param zHalf Half length of the z side.
		 * \return The inertia tensor.
		 */
		static glm::mat3 generateCubeTensor(real mass, real xHalf, real yHalf, real zHalf);
		/**
		 * \brief Generate an inertia tensor for a sphere shape.
		 * \param mass The mass of the object.
		 * \param radius The radius of the sphere.
		 * \return The inertia tensor.
		 */
		static glm::mat3 generateSphereTensor(real mass, real radius);

	private:
		InertiaTensorGenerator() = default;
		~InertiaTensorGenerator() = default;
	};
}
