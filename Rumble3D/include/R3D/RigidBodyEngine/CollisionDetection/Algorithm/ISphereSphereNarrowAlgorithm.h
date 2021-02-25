#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	class CollisionSphere;

	/**
	 * \brief Interface for sphere-sphere narrow algorithms.
	 */
	class R3D_DECLSPEC ISphereSphereNarrowAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~ISphereSphereNarrowAlgorithm() = default;

		/**
		 * \brief Generate contacts between two rigid bodies with
		 * sphere collision primitives.
		 * \param first The first participating rigid body.
		 * \param second The second participating rigid body.
		 * \param[out] collisionData All newly generated contacts will
		 * be put in here.
		 * \return True if new contacts have been generated, false
		 * otherwise.
		 */
		bool generateContactData(RigidBody* first,
								 RigidBody* second,
                                 FixedSizeContainer<Contact>& collisionData) override final;

	protected:
		/**
		 * \brief Generate contacts between two collision spheres.
		 * \param rbSphere1 First rigid body with sphere primitive.
		 * \param sphere1 CollisionSphere of rbSphere1.
		 * \param rbSphere2 Second rigid body with sphere primitive.
		 * \param sphere2 CollisionSphere of rbSphere2.
		 * \param[out] collisionData All newly generated contacts will
		 * be put in here.
		 * \return True if new contacts have been generated, false
		 * otherwise.
		 */
		virtual bool generateContactDataImpl(RigidBody* rbSphere1, CollisionSphere* sphere1,
											 RigidBody* rbSphere2, CollisionSphere* sphere2,
                                             FixedSizeContainer<Contact>& collisionData) = 0;

		explicit ISphereSphereNarrowAlgorithm() = default;
	};
}