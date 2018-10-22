#pragma once
#include "R3D/RigidBodyEngine/CollisionObject.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionMask.h"
#include "R3D/RigidBodyEngine/RigidBodyDef.h"
#include "R3D/Common/Precision.h"
#include "R3D/Common/Common.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "R3D/Transform3D.h"


namespace r3 
{
	class PhysicsMaterial;

	/**
	 * \brief A rigid body is a 3D object, which can be moved and
	 * rotated and has collision properties.
	 */
	class R3D_DECLSPEC RigidBody : public CollisionObject
	{
	public:
		explicit RigidBody();
		/**
		 * \brief RigidBody constructor.
		 * \param def Rigid body construction information.
		 */
		explicit RigidBody(const RigidBodyDef& def);
		~RigidBody();
	
		/** 
		 * \brief Initialize all attributes of this rigid body. 
		 * param definition Rigid body construction information.
		 */
		void init(const RigidBodyDef& definition);

		void calculateDerivedData();
		/** 
		 * \brief Set the current inertia tensor. 
		 * \param inertiaTensor The new inertia tensor.
		 */
		void setInertiaTensor(const glm::mat3& inertiaTensor);
		/**
		 * \brief Get the inverted inertia tensor. 
		 * \return The inverse of the current inertia tensor.
		 */
		glm::mat3 getInverseTensor() const;

		/**
		 * \brief Set the mass of this rigid body.
		 * \param mass The new mass.
		 * \details Implicitly sets the inverse mass.
		 */
		void setMass(real mass);
		/** 
		 * \brief Get the mass of this rigid body. 
		 * \return The current mass.
		 */
		real getMass() const;
		/**
		 * \brief Set the inverse mass of this rigid body.
		 * \param inverseMass An inverse mass of zero equals a rigid body
		 * with infinite mass.
		 * \details Implicitly sets the mass.
		 */
		void setInverseMass(real inverseMass);
		/** 
		 * \brief Get the inverse mass.
		 * \return The inverse of the current mass.
		 * \details An inverse mass of zero equals a rigid body
		 * with infinite mass.
		 */
		real getInverseMass() const;
		/** 
		 * \brief Check if this rigid body has infinite mass.
		 * \return True if the mass is infinite, false otherwise.
		 */
		bool hasFiniteMass() const;

		/**
		 * \brief Get the current sum of linear forces.
		 * \return The force accumulator.
		 */
		glm::vec3 getForceAccumulated() const;
		/**
		 * \brief Get the current sum of rotational forces.
		 * \return The torque accumulator.
		 */
		glm::vec3 getTorqueAccumulated() const;

		/** 
		 * \brief Set the position of this rigid body. 
		 * \param centerOfMass The new position.
		 */
		void setCenterOfMass(const glm::vec3& centerOfMass);
		/** 
		 * \brief Set the position of this rigid body.
		 * \param x The x-component of the new position.
		 * \param y The y-component of the new position.
		 * \param z The z-component of the new position.
		 */
		void setCenterOfMass(real x, real y, real z);
		/** 
		 * \brief Get the current position.
		 * \return The position.
		 */
		glm::vec3 getCenterOfMass() const;

		/**
		 * \brief Set the current orientation.
		 * \param orientation The new orientation.
		 */
		void setOrientation(const glm::quat& orientation);
		/**
		 * \brief Set the current orientation.
		 * \param r The radius in radians
		 * \param i The x component of the rotation axis.
		 * \param j The y component of the rotation axis.
		 * \param k The z component of the rotation axis.
		 */
		void setOrientation(real r, real i, real j, real k);
		/**
		 * \brief Get the current orientation.
		 * \return The orientation.
		 */
		glm::quat getOrientation() const;

		/**
		 * \brief Set the current orientation.
		 * \param rotation The new rotation.
		 */
		void setRotation(const glm::vec3& rotation);
		/**
		 * \brief Set the current orientation.
		 * \param x The x-component of the new orientation.
		 * \param y The y-component of the new orientation.
		 * \param z The z-component of the new orientation.
		 */
		void setRotation(real x, real y, real z);
		/**
		 * \brief Get the current orientation.
		 * \return The orientation.
		 */
		glm::vec3 getRotation() const;

		/** 
		 * \brief Set the current velocity.
		 * \param velocity The new velocity.
		 */
		void setVelocity(const glm::vec3& velocity);
		/** 
		 * \brief Set the current velocity. 
		 * \param x The x-component of the new velocity.
		 * \param y The y-component of the new velocity.
		 * \param z The z-component of the new velocity.
		 */
		void setVelocity(real x, real y, real z);
		/** 
		 * \brief Get the current velocity. 
		 * \return The velocity.
		 */
		glm::vec3 getVelocity() const;

		/** 
		 * \brief Set the current acceleration.
		 * \param acceleration The new acceleration.
		 */
		void setAcceleration(const glm::vec3& acceleration);
		/** 
		 * \brief Set the current acceleration.
		 * \param x The x-component of the new acceleration
		 * \param y The y-component of the new acceleration
		 * \param z The z-component of the new acceleration
		 */
		void setAcceleration(real x, real y, real z);
		/** 
		 * \brief Get the current acceleration. 
		 * \return The acceleration.
		 */
		glm::vec3 getAcceleration() const;

		/** 
		 * \brief Set the linear damping coefficient. 
		 * \param linearDamping The new linear damping coefficient.
		 */
		void setLinearDamping(real linearDamping);
		/** 
		 * \brief Get the linear damping factor.
		 * \return The linear damping coefficient.
		 */
		real getLinearDamping() const;
		/** 
		 * \brief Get the angular damping coefficient. 
		 * \param angularDamping The new angular damping coefficient.
		 */
		void setAngularDamping(real angularDamping);
		/** 
		 * \brief Get the angular damping coefficient. 
		 * \return The angular damping coefficient.
		 */
		real getAngularDamping() const;

		
		/** 
		 * \brief Get the current transformation matrix. 
		 * \return The transformation matrix.
		 */
		glm::mat4 getTransformationMatrix() const;
		/**
		 * \brief Get the inverted inertia tensor in world coordinates.
		 * \param[out] inverseInertiaTensorWorld Contains the inverted
		 * inertia tensor.
		 */
		void getInverseInertiaTensorWorld(glm::mat3* inverseInertiaTensorWorld) const;

		/**
		 * \brief Additively increase velocity.
		 * \param deltaVelocity The summand.
		 */
		void addVelocity(const glm::vec3& deltaVelocity);
		/**
		 * \brief Additively increase rotation.
		 * \param deltaRotation The summand.
		 */
		void addRotation(const glm::vec3& deltaRotation);

		/** 
		 * \brief Check if this rigid body is being simulated. 
		 * \return True if it is being siulated, false otherwise.
		 */
		bool isAwake() const;
		/** 
		 * \brief Start or stop simulating this rigid body.
		 * \param awake The new awake state.
		 */
		void setAwake(bool awake);

		/**
		 * \brief Set the physics material. 
		 * \param material The new physics material.
		 */
		void setPhysicsMaterial(PhysicsMaterial* material);
		/** 
		 * \brief Get the current physics material.
		 * \return The current physics material if existent, nullptr otherwise.	 
		 */
		PhysicsMaterial* getPhysicsMaterial() const;

		/**
		 * \brief Reset accumulated linear and angular forces.
		 */
		void clearAccumulators();              
		/**
		 * \brief Add a force which's attack point is the bodies
		 * center of mass.
		 * \param force The force to be added.
		 */
		void addForce(const glm::vec3 & force); 
		/** 
		 * \brief Add a force at a specified body point. Can create
		 * rotational forces.
		 * \param force The force to be applied 
		 * \param point The attack point of the force in world coordinates.
		 */
		void addForceAtPoint(const glm::vec3 & force, const glm::vec3 & point);
		/**
		 * \brief Add a force at a specified body point. Can create
		 * rotational forces.
		 * \param force The force to be applied
		 * \param point The attack point of the force in local body 
		 * coordinates.
		 */
		void addForceAtBodyPoint(const glm::vec3 & force, const glm::vec3 & point);
		/** 
		 * \brief Additively increase torque accumulator..
		 * \param torque The torque to be added.
		*/
		void addTorque(const glm::vec3 & torque);

		/**
		 * \brief Convert a point into local body space.
		 * \param point The point to convert.
		 * \return The point in local body space.
		 */
		glm::vec3 getPointInLocalSpace(const glm::vec3 &point) const;
		/**
		 * \brief Convert a point from local body space into world
		 * space.
		 * \param point A point in local body space.
		 * \return The converted point in world space.
		 */
		glm::vec3 getPointInWorldSpace(const glm::vec3 &point) const;
		/**
		 * \brief Convert a direction from world space into local
		 * space.
		 * \param direction The direction in world space.
		 * \return The direction in local space.
		 */
		glm::vec3 getDirectionInLocalSpace(const glm::vec3 &direction) const;
		/**
		 * \brief Convert a direction from local body space into
		 * world space.
		 * \param direction The direction in local body space.
		 * \return The direction in world space.
		 */
		glm::vec3 getDirectionInWorldSpace(const glm::vec3 &direction) const;

		/** Bestimmung des neuen Ortes für das Teilchen. */
		/**
		 * \brief Resolve position and rotation
		 * \param duration The duration to integrate over.
		 */
		virtual void integrate(real duration);

	protected:
		PhysicsMaterial* m_physicsMaterial{};
		CollisionMask m_collisionMask;

		real m_mass;
		real m_inverseMass{};
		
		real m_linearDamping{};
		real m_angularDamping{};

		/*glm::vec3 m_centerOfMass;
		glm::quat m_orientation;*/
		
		glm::vec3 m_velocity;
		glm::vec3 m_acceleration;
		glm::vec3 m_lastFrameAcceleration; // Beschleunigung im letzten Frame ???
		glm::vec3 m_rotation;

		glm::mat4 m_transformationMatrix;
		glm::mat3 m_inverseInertiaTensor;
		glm::mat3 m_inverseInertiaTensorWorld;

		/* Accumulators */
		glm::vec3 m_forceAccumulated;
		glm::vec3 m_torqueAccumulated;
		bool m_awake = false;

		static void calculateTransformationMatrix(glm::mat4& transformationMatrix,
												  const glm::vec3& position,
												  const glm::mat3& orientation);

		static void transformInertiaTensor(glm::mat3& iitWorld,
										   const glm::mat3& iit,
										   const glm::mat4& rotMat);
	};
}

 