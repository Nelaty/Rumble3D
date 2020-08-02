#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3 
{
	class RigidBody;

	/**
	 * \brief Interface for rigid body force generators.
	 */
	class R3D_DECLSPEC ForceGenerator
	{
	public:
		virtual ~ForceGenerator();

		/**
		 * \brief Apply force to a rigid body over a specific time.
		 * \param body The rigid body on which to apply force.
		 * \param duration The duration over which the force acts.
		 */
		virtual void updateForce(RigidBody* body, real duration) = 0;

	protected:
		explicit ForceGenerator();
	};
}
