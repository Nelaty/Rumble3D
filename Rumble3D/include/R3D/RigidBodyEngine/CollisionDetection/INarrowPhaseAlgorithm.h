#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"

namespace r3
{
	/**
	 * \brief Interface for a narrow phase algorithm, which can
	 * generate new contacts between one specific pair of collision
	 * primitives, i.e. sphere-sphere, box-sphere. 
	 * 
	 */
	class R3D_DECLSPEC INarrowPhaseAlgorithm
	{
	public:
		virtual ~INarrowPhaseAlgorithm();

		/**
		 * \brief Generate contacts between two rigid bodies.
		 * \param first The first participating rigid body.
		 * \param second The second participating rigid body.
		 * \param collisionData All newly generated contacts will
		 * be put in here.
		 * \return True if new contacts have been generated, false
		 * otherwise.
		 */
		virtual bool generateContactData(RigidBody* first,
										 RigidBody* second,
										 CollisionData& collisionData) = 0;

	protected:
		explicit INarrowPhaseAlgorithm();
	};
}
