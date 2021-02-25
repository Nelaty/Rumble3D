#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionPlane.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Interface for plane-plane narrow algorithms.
	 */
	class R3D_DECLSPEC IPlanePlaneCollisionAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IPlanePlaneCollisionAlgorithm() = default;

		bool generateContactData(RigidBody* first, 
								 RigidBody* second,
                                 FixedSizeContainer<Contact>& collisionData) override final;

	protected:
		virtual bool generateContactDataImpl(RigidBody* rbPlane1, CollisionPlane* plane1,
											 RigidBody* rbPlane2, CollisionPlane* plane2,
                                             FixedSizeContainer<Contact>& collisionData) = 0;

		explicit IPlanePlaneCollisionAlgorithm() = default;
	};
}
