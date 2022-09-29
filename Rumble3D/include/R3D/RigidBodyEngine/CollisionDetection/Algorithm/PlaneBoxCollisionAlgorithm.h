#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IPlaneBoxCollisionAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Default implementation for a plane-box narrow algorithm.
	 */
	class R3D_EXPORT PlaneBoxCollisionAlgorithm : public IPlaneBoxCollisionAlgorithm
	{
	public:
		explicit PlaneBoxCollisionAlgorithm() = default;
		~PlaneBoxCollisionAlgorithm() = default;

	protected:
		bool generateContactDataImpl(RigidBody* rbPlane,
									 CollisionPlane* plane, 
									 RigidBody* rbBox,
									 CollisionBox* box,
                                     FixedSizeContainer<Contact>& collisionData) override;
	};
}
