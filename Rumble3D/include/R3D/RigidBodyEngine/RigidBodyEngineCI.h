#pragma once
#include "R3D/IComputationInterface.h"
#include "R3D/Common/Common.h"

#include "R3D/RigidBodyEngine/CollisionDetection/CollisionDetector.h"

namespace r3
{
	class ICollisionResolverAccess;

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
<<<<<<< Updated upstream
		/** Get the currently used rigid body world. */
=======
		/** 
		 * \brief Get the currently used rigid body world. 
		 * \return The rigid body world.
		 */
>>>>>>> Stashed changes
		RigidBodyWorld* getRigidBodyWorld() const;

	protected:
		explicit RigidBodyEngineCI(RigidBodyWorld* rigidBodyWorld = nullptr);

		CollisionDetector m_collisionDetector;
		std::unique_ptr<ICollisionResolverAccess> m_collisionResolver;

		RigidBodyWorld* m_rigidBodyWorld;
	};
}