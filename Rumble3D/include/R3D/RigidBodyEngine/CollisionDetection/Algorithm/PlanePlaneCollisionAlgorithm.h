#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IPlanePlaneCollisionAlgorithm.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Default implementation for a plane-plane narrow algorithm.
	 */
	class R3D_EXPORT PlanePlaneCollisionAlgorithm : public IPlanePlaneCollisionAlgorithm
	{
	public:
		explicit PlanePlaneCollisionAlgorithm() = default;
		~PlanePlaneCollisionAlgorithm() = default;

	protected:
		bool generateContactDataImpl(RigidBody* rbPlane1,
									 CollisionPlane* plane1,
									 RigidBody* rbPlane2,
									 CollisionPlane* plane2,
                                     FixedSizeContainer<Contact>& collisionData) override;
	};
}
