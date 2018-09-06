#pragma once
#include "R3D/PhysicsEngineModule.h"
#include "R3D/Common/Common.h"

#include "R3D/RigidBodyEngine/RigidBodyDef.h"
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

		/**
		* \brief Allocate space for a new rigid body and register it.
		* \param definition Construction information for the new rigid body.
		* \return The new rigid body.
		*/
		RigidBody* createRigidBody(RigidBodyDef definition = RigidBodyDef());
		/**
		* \brief Free memory of a given rigid body.
		* \param particle The rigid body to destroy.
		* \return True if the rigid body was found, false otherwise.
		*/
		bool destroyRigidBody(RigidBody* particle);
		/**
		* \brief Free memory of all rigid bodies.
		*/
		void destroyAllRigidBodies();

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