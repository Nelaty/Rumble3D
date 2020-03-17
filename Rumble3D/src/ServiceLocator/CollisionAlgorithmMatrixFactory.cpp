#include "R3D/Helper/CollisionAlgorithmMatrixFactory.h"

#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPrimitiveType.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/BoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/BoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/SphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlanePlaneCollisionAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlaneSphereCollisionAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlaneBoxCollisionAlgorithm.h"

namespace r3
{
	CollisionAlgorithmMatrix CollisionAlgorithmMatrixFactory::getMatrix()
	{
		CollisionAlgorithmMatrix matrix;
		matrix.setAlgorithm(std::make_shared<BoxBoxNarrowAlgorithm>(),
							R3D_PRIMITIVE_BOX,
							R3D_PRIMITIVE_BOX);

		matrix.setAlgorithm(std::make_shared<BoxSphereNarrowAlgorithm>(),
							R3D_PRIMITIVE_BOX,
							R3D_PRIMITIVE_SPHERE);

		matrix.setAlgorithm(std::make_shared<SphereSphereNarrowAlgorithm>(),
							R3D_PRIMITIVE_SPHERE,
							R3D_PRIMITIVE_SPHERE);

		matrix.setAlgorithm(std::make_shared<PlanePlaneCollisionAlgorithm>(),
							R3D_PRIMITIVE_PLANE,
							R3D_PRIMITIVE_PLANE);

		matrix.setAlgorithm(std::make_shared<PlaneBoxCollisionAlgorithm>(),
							R3D_PRIMITIVE_PLANE,
							R3D_PRIMITIVE_BOX);

		matrix.setAlgorithm(std::make_shared<PlaneSphereCollisionAlgorithm>(),
							R3D_PRIMITIVE_PLANE,
							R3D_PRIMITIVE_SPHERE);

		return matrix;
	}

	CollisionAlgorithmMatrixFactory::CollisionAlgorithmMatrixFactory()
	{
	}

	CollisionAlgorithmMatrixFactory::~CollisionAlgorithmMatrixFactory()
	{
	}
}
