#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionPlane.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Interface for plane-box narrow algorithms.
	 */
	class R3D_EXPORT IPlaneBoxCollisionAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IPlaneBoxCollisionAlgorithm() = default;

		bool generateContactData(RigidBody* first, 
								 RigidBody* second,
                                 FixedSizeContainer<Contact>& collisionData) override final;
	
	protected:
		explicit IPlaneBoxCollisionAlgorithm() = default;

		virtual bool generateContactDataImpl(RigidBody* rbPlane, CollisionPlane* plane,
											 RigidBody* rbBox, CollisionBox* box,
                                             FixedSizeContainer<Contact>& collisionData) = 0;
	};
}
