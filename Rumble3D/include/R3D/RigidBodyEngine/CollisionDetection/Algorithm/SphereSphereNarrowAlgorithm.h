#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/ISphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Default implementation for a sphere-sphere narrow algorithm.
	 */
	class R3D_DECLSPEC SphereSphereNarrowAlgorithm : public ISphereSphereNarrowAlgorithm
	{
	public:
		explicit SphereSphereNarrowAlgorithm() = default;
		~SphereSphereNarrowAlgorithm() = default;

	protected:
		bool generateContactDataImpl(RigidBody* rbSphere1, CollisionSphere* sphere1,
									 RigidBody* rbSphere2, CollisionSphere* sphere2,
                                     FixedSizeContainer<Contact>& collisionData) override;
	};
}
