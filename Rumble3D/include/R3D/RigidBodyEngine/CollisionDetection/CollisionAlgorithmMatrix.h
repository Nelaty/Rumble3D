#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPrimitiveType.h"

#include "R3D/Common/Common.h"

#include <memory>
#include <array>

namespace r3
{
	class INarrowPhaseAlgorithm;
	class NullAlgorithm;

	/**
	 * \brief Describes a collision algorithm for every collision
	 * primitive type combination.
	 */
	class R3D_DECLSPEC CollisionAlgorithmMatrix
	{
	public:
		using Algorithm_Ptr = std::shared_ptr<INarrowPhaseAlgorithm>;

		explicit CollisionAlgorithmMatrix();
		~CollisionAlgorithmMatrix() = default;

		/**
		 * \brief Set the collision algorithm for a specific
		 * collision primitive combination.
		 * \param algorithm The algorithm to use for the specified
		 * combination.
		 * \param firstShape The type of the first primitive shape.
		 * \param secondShape The type of the second shape.
		 */
		void setAlgorithm(const Algorithm_Ptr& algorithm,
						  CollisionPrimitiveType firstShape,
						  CollisionPrimitiveType secondShape);

		/**
		 * \brief Get the collision algorithm currently used for
		 * a specific collision primitive combination.
		 * \param firstShape The type of the first primitive shape.
		 * \param secondShape The type of the second primitive shape.
		 * \return The collision algorithm if existent, a null object
		 * otherwise.
		 */
		INarrowPhaseAlgorithm* getAlgorithm(CollisionPrimitiveType firstShape,
											CollisionPrimitiveType secondShape);

		/**
		 * \brief Replace all algorithms with a null algorithm.
		 */
		void reset();

	private:
		/**
		 * \brief Default initialization of the collision algorithm
		 * matrix.
		 */
		void init();

		/** Null-object: Algorithm that does nothing. */
		std::shared_ptr<NullAlgorithm> m_nullAlgorithm{};

		static constexpr int s_algCount = R3D_PRIMITIVE_TYPE_COUNT;
		std::array<std::array<Algorithm_Ptr, s_algCount>, s_algCount> m_algorithms{};
	};
}