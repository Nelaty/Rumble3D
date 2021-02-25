#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/IBoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Default implementation for a box-sphere narrow algorithm.
	 */
	class R3D_DECLSPEC BoxSphereNarrowAlgorithm : public IBoxSphereNarrowAlgorithm
	{
	public:
		explicit BoxSphereNarrowAlgorithm() = default;
		~BoxSphereNarrowAlgorithm() = default;

	protected:
		bool generateContactDataImpl(RigidBody* rbBox, CollisionBox* box,
									 RigidBody* rbSphere, CollisionSphere* sphere,
                                     FixedSizeContainer<Contact>& collisionData) override;

	};
}
