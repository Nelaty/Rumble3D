#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionPlane.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

#include "BoxBoxNarrowAlgorithm.h"

namespace r3
{
	/**
	 * \brief Interface for plane-sphere narrow algorithms.
	 */
	class R3D_DECLSPEC IPlaneSphereCollisionAlgorithm : public INarrowPhaseAlgorithm
	{
	public:
		virtual ~IPlaneSphereCollisionAlgorithm() = default;

		/**
		 * \brief Generate contacts between two rigid bodies one with
		 * a sphere collision primitive and one with a plane collision
		 * primitives.
		 * \param first The first participating rigid body.
		 * \param second The second participating rigid body.
		 * \param[out] collisionData All newly generated contacts will
		 * be put in here.
		 * \return True if new contacts have been generated, false
		 * otherwise.
		 */
		bool generateContactData(RigidBody* first, 
								 RigidBody* second, 
								 CollisionData& collisionData) override final;

	protected:
		explicit IPlaneSphereCollisionAlgorithm() = default;

		/**
		 * \brief Generate contacts between a plane and a sphere.
		 */
		virtual bool generateContactDataImpl(RigidBody* rbPlane, CollisionPlane* plane,
											 RigidBody* rbSphere, CollisionSphere* sphere,
											 CollisionData& collisionData) = 0;
	};
}
