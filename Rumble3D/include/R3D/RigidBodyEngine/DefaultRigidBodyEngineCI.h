#pragma once
#include "RigidBodyEngineCI.h"
#include "R3D/Common/Common.h"

#include <memory>

namespace r3
{
	class ICollisionResolverAccess;

	/**
	 * \brief Default implementation of the rigid body engine
	 * computation interface.
	 */
	class R3D_DECLSPEC DefaultRigidBodyEngineCI : public RigidBodyEngineCI
	{
	public:
		explicit DefaultRigidBodyEngineCI();
		~DefaultRigidBodyEngineCI() = default;

		/**
		 * \brief Prepare rigid bodies.
		 */
		void onBegin() override;
		/**
		 * \brief Update forces on rigid bodies.
		 * \param timeDelta Time step of the simulation update.
		 */
		void step(real timeDelta) override;
		/**
		 * \brief Update positions, rotations and resolve collisions.
		 * \param timeDelta Time step of the simulation update.
		 */
		void integrate(real timeDelta) override;
		/**
		 * \brief Clear accumulators
		 */
		void onEnd() override;

		/**
		 * \brief Reset the computation interface.
		 */
		void reset() override;

	private:
		/**
		 * \brief Initialize the computation interface.
		 */
		void init();
	};
}
