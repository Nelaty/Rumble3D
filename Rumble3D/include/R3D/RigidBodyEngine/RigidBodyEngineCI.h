#pragma once
#include "R3D/Common/Common.h"
#include "R3D/IComputationInterface.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionDetector.h"

namespace r3
{
	class ICollisionResolverAccess;

	class RigidBodyWorld;

	/**
	 * \brief Abstract class for computation interfaces used by rigid
	 * body worlds.
	 */
	class R3D_DECLSPEC RigidBodyEngineCI : public IComputationInterface
	{
	public:
		virtual ~RigidBodyEngineCI();

		/** 
		 * \brief Set the rigid body world, used for rigid body
		 * calculations. 
		 * \param rigidBodyWorld The related rigid body world.
		 */
		void setRigidBodyWorld(RigidBodyWorld* rigidBodyWorld);
		/** 
		 * \brief Get the currently used rigid body world. 
		 * 
		 */
		RigidBodyWorld* getRigidBodyWorld() const;

	protected:
		/**
		 * \brief RigidBodyEngineCI constructor
		 * \param rigidBodyWorld The world used for rigid body calculations.
		 */
		explicit RigidBodyEngineCI(RigidBodyWorld* rigidBodyWorld = nullptr);

		CollisionDetector m_collisionDetector;
		std::unique_ptr<ICollisionResolverAccess> m_collisionResolver;

		RigidBodyWorld* m_rigidBodyWorld;
	};
}