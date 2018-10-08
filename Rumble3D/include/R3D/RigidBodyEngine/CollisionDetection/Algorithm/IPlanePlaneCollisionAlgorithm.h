#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionPlane.h"

namespace r3
{
	class IPlanePlaneCollisionAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IPlanePlaneCollisionAlgorithm();

		bool generateContactData(RigidBody* first, 
								 RigidBody* second,
								 CollisionData& collisionData) override final;

	protected:
		virtual bool generateContactDataImpl(RigidBody* rbPlane1, CollisionPlane* plane1,
											 RigidBody* rbPlane2, CollisionPlane* plane2,
											 CollisionData& collisionData) = 0;

		explicit IPlanePlaneCollisionAlgorithm();
	};
}
