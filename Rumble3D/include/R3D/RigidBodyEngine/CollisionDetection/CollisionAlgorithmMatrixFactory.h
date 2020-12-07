#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrix.h"

namespace r3
{
	/**
	 * \brief Generate a CollisionAlgorithmMatrix with default 
	 * narrow phase collision detection and contact generation
	 * algorithms.
	 */
	class CollisionAlgorithmMatrixFactory
	{
	public:
		/**
		 * \brief Generate a default CollisionAlgorithmMatrix.
		 * \return The CollisionAlgorithmMatrix.
		 */
		static CollisionAlgorithmMatrix getMatrix();

	private:
		explicit CollisionAlgorithmMatrixFactory();
		~CollisionAlgorithmMatrixFactory();
	};
}
