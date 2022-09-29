#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IPlaneSphereCollisionAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Default implementation for a plane-sphere narrow algorithm.
	 */
	class R3D_EXPORT PlaneSphereCollisionAlgorithm : public IPlaneSphereCollisionAlgorithm
	{
	public:
		explicit PlaneSphereCollisionAlgorithm() = default;
		~PlaneSphereCollisionAlgorithm() = default;

	protected:
		bool generateContactDataImpl(RigidBody* rbPlane, 
									 CollisionPlane* plane,
									 RigidBody* rbSphere,
									 CollisionSphere* sphere,
                                     FixedSizeContainer<Contact>& collisionData) override;
	};
}
