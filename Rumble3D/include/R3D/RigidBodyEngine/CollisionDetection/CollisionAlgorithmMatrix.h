#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPrimitiveType.h"

#include <array>
#include <memory>

namespace r3
{
	class INarrowPhaseAlgorithm;

	class R3D_DECLSPEC CollisionAlgorithmMatrix
	{
	public:
		explicit CollisionAlgorithmMatrix();
		~CollisionAlgorithmMatrix();

		void setAlgorithm(INarrowPhaseAlgorithm* algorithm,
						  CollisionPrimitiveType firstShape,
						  CollisionPrimitiveType secondShape);

		INarrowPhaseAlgorithm* getAlgorithm(CollisionPrimitiveType firstShape,
											CollisionPrimitiveType secondShape);

	private:
		void freeMemory(CollisionPrimitiveType firstShape,
						CollisionPrimitiveType secondShape);

		std::array<std::array<INarrowPhaseAlgorithm*, R3D_PRIMITIVE_SPHERE>, R3D_PRIMITIVE_SPHERE> m_algorithms;
	};
}