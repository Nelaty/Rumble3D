#include "R3D/ServiceLocator/ServiceLocatorCollisionAlgorithmMatrix.h"

#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPrimitiveType.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/SphereSphereNarrowAlgorithm.h"

namespace r3
{
	CollisionAlgorithmMatrix ServiceLocatorCollisionAlgorithmMatrix::getMatrix()
	{
		CollisionAlgorithmMatrix matrix;
		matrix.setAlgorithm(new BoxBoxNarrowAlgorithm(),
							R3D_PRIMITIVE_BOX,
							R3D_PRIMITIVE_BOX);

		matrix.setAlgorithm(new BoxSphereNarrowAlgorithm(),
							R3D_PRIMITIVE_BOX,
							R3D_PRIMITIVE_SPHERE);

		matrix.setAlgorithm(new SphereSphereNarrowAlgorithm(),
							R3D_PRIMITIVE_SPHERE,
							R3D_PRIMITIVE_SPHERE);
		return matrix;
	}

	ServiceLocatorCollisionAlgorithmMatrix::ServiceLocatorCollisionAlgorithmMatrix()
	= default;

	ServiceLocatorCollisionAlgorithmMatrix::~ServiceLocatorCollisionAlgorithmMatrix()
	= default;
}
