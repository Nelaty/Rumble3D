#include "R3D/RigidBodyEngine/CollisionDetection/CollisionAlgorithmMatrix.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/NullAlgorithm.h"

#include <cassert>

namespace r3
{
	CollisionAlgorithmMatrix::CollisionAlgorithmMatrix()
		: m_nullAlgorithm(nullptr)
	{
		init();
	}

	void CollisionAlgorithmMatrix::setAlgorithm(const Algorithm_Ptr& algorithm,
	                                            const CollisionPrimitiveType firstShape,
	                                            const CollisionPrimitiveType secondShape)
	{
		m_algorithms[firstShape][secondShape] = algorithm;
		m_algorithms[secondShape][firstShape] = algorithm;
	}

	INarrowPhaseAlgorithm* CollisionAlgorithmMatrix::getAlgorithm(const CollisionPrimitiveType firstShape,
	                                                              const CollisionPrimitiveType secondShape)
	{
		const auto algorithm = m_algorithms[firstShape][secondShape];
		return algorithm.get();
	}

	void CollisionAlgorithmMatrix::reset()
	{
		for(auto& outer : m_algorithms)
		{
			for(auto& algorithm : outer)
			{
				algorithm = m_nullAlgorithm;
			}
		}
	}

	void CollisionAlgorithmMatrix::init()
	{
		m_nullAlgorithm = std::make_shared<NullAlgorithm>();
		reset();
	}
}
