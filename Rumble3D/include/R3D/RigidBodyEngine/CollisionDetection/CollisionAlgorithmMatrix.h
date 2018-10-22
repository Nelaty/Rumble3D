#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPrimitiveType.h"

#include "R3D/Common/Common.h"

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

		void init();

		static constexpr int s_algCount = R3D_PRIMITIVE_TYPE_COUNT;
		std::array<std::array<INarrowPhaseAlgorithm*, s_algCount>, s_algCount> m_algorithms{};
	};
}