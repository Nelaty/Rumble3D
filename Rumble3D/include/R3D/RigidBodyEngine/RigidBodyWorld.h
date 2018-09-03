#pragma once
#include "R3D/PhysicsEngineModule.h"
#include "R3D/Common/Common.h"

#include "R3D/RigidBodyEngine/ForceRegistry.h"

#include <vector>

namespace r3 
{
	class ForceGenerator;
	class RigidBody;

	class RigidBodyEngineCI;

	class R3D_DECLSPEC RigidBodyWorld : public PhysicsEngineModule
	{
	public:
		using RigidBodies = std::vector<RigidBody*>;
		
		RigidBodyWorld();
		~RigidBodyWorld();

		/** Set the computation interface, which simulates the rigid bodies. */
		void setComputationInterface(RigidBodyEngineCI* computationInterface);
		/** Get the currently used computation interface. */
		IComputationInterface* getComputationInterface() const override;

		/** Register a new rigid body, which should be simulated. */
		void registerRigidBody(RigidBody* rb);
		/** Unregister an already registered rigid body. */
		bool unregisterRigidBody(RigidBody* rb);
		/** Unregister all registered rigid bodies. */
		void unregisterAllRigidBodies();

		/** Get all currently registered rigid bodies. */
		RigidBodies& getRigidBodies();
		/** Get all currently registered rigid bodies. */
		const RigidBodies& getRigidBodies() const;

		/** 
		 * Get the force registry, which holds all currently active force
		 * generators.
		 */
		ForceRegistry& getForceRegistry();
		/**
		* Get the force registry, which holds all currently active force
		* generators.
		*/
		const ForceRegistry& getForceRegistry() const;

	private:
		RigidBodyEngineCI* m_computationInterface{};

		RigidBodies m_rigidBodies;
		ForceRegistry m_forceRegistry;
	};
}