#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/BroadPhaseCollision.h"

namespace rum
{
	INarrowPhaseFilter::~INarrowPhaseFilter()
	= default;

	INarrowPhaseFilter::INarrowPhaseFilter()
	= default;

	void INarrowPhaseFilter::generateCollisionData(CollisionSphere* first, CollisionBox* second)
	{
		generateCollisionData(second, first);
	}
}
