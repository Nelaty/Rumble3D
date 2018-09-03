#pragma once
#include "R3D/IComputationInterface.h"
#include "R3D/Common/Common.h"

namespace r3
{
	class RigidBodyWorld;

	/**
	* \brief Abstract class for computation interfaces used for rigid body
	* worlds.
	*/
	class R3D_DECLSPEC RigidBodyEngineCI : public IComputationInterface
	{
	public:
		virtual ~RigidBodyEngineCI();

		/** Set the rigid body world, used for rigid body calculations. */
		void setRigidBodyWorld(RigidBodyWorld* rigidBodyWorld);
		/** Get the currently used rigid body world. */
		RigidBodyWorld* getRigidBodyWorld() const;

	protected:
		explicit RigidBodyEngineCI(RigidBodyWorld* rigidBodyWorld = nullptr);

		RigidBodyWorld* m_rigidBodyWorld;
	};
}