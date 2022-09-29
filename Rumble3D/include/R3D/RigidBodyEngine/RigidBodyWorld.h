#pragma once
#include "R3D/Common/Common.h"
#include "R3D/PhysicsEngineModule.h"
#include "R3D/RigidBodyEngine/RigidBodyDef.h"
#include "R3D/RigidBodyEngine/ForceRegistry.h"

#include <vector>

namespace r3 
{
	class ForceGenerator;
	class RigidBody;

	class RigidBodyEngineCI;

	/**
	 * \brief A RigidBodyWorld is a physics engine module, used to
	 * simulate rigid bodies.
	 */
	class R3D_EXPORT RigidBodyWorld : public PhysicsEngineModule
	{
	public:
		using RigidBody_Container = std::vector<RigidBody*>;
		
		RigidBodyWorld() = default;
		~RigidBodyWorld() = default;

		/** 
		 * \brief Set the computation interface, which simulates the rigid bodies.
		 * \param computationInterface The new computation interface.
		 */
		void setComputationInterface(RigidBodyEngineCI* computationInterface);
		/** 
		 * \brief Get the world's computation interface. 
		 * \return The current computation interface.
		 */
		IComputationInterface* getComputationInterface() const override;

		/** 
		 * \brief Register a new rigid body.
		 * \param body The rigid body to register.
		 */
		void addRigidBody(RigidBody* body);

		/**
		 * \brief Unregister an already registered rigid body.
		 * \param body The rigid body to unregister.
		 */
		void removeRigidBody(RigidBody* body);

		/** 
		 * \brief Get the world's rigid bodies. 
		 * \return All currently registered rigid bodies.
		 */
		RigidBody_Container& getRigidBodies();
		/**
		* \brief Get the world's rigid bodies.
		* \return All currently registered rigid bodies.
		*/
		const RigidBody_Container& getRigidBodies() const;

		/** 
		 * \brief Get the force registry, which holds all currently 
		 * active force generators.
		 * \return The force registry.
		 */
		ForceRegistry& getForceRegistry();
		/**
		* \brief Get the force registry, which holds all currently
		* active force generators.
		* \return The force registry.
		*/
		const ForceRegistry& getForceRegistry() const;

	private:
		RigidBodyEngineCI* m_computationInterface{};

		RigidBody_Container m_rigidBodies;
		ForceRegistry m_forceRegistry;
	};
}