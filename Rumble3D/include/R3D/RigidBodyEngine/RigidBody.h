#pragma once
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace rum 
{
	class RigidBody
	{
	public:
		void calculateDerivedData();
		void setInertiaTensor(const glm::mat3& inertiaTensor);
		glm::mat3 getInverseTensor();

		/* (Inverse) Mass access */
		void setMass(const real mass);
		real getMass() const;
		void setInverseMass(const real inverseMass);
		real getInverseMass() const;
		bool hasFiniteMass();

		/* Force and torque accumulator access */
		glm::vec3 getForceAccumulated();
		glm::vec3 getTorqueAccumulated();

		/* Position access */
		void setPosition(const glm::vec3& position);
		void setPosition(const real x, const real y, const real z);
		//void getPosition(glm::vec3 * position) const;
		glm::vec3 getPosition() const;

		/* Velocity access */
		void setVelocity(const glm::vec3& velocity);
		void setVelocity(const real x, const real y, const real z);
		//void getVelocity(glm::vec3 *velocity) const;
		glm::vec3 getVelocity() const;

		/* Acceleration access */
		void setAcceleration(const glm::vec3& acceleration);
		void setAcceleration(const real x, const real y, const real z);
		//void getAcceleration(glm::vec3 &acceleration) const;
		glm::vec3 getAcceleration() const;

		/* Linear and angular damping access */
		void setLinearDamping(const real linearDamping);
		real getLinearDamping() const;
		void setAngularDamping(const real angularDamping);
		real getAngularDamping() const;

		void setOrientation(const glm::quat& orientation);
		void setOrientation(const real r, const real i, const real j, const real k);
		glm::quat getOrientation() const;
		void setRotation(const glm::vec3& rotation);
		void setRotation(const real x, const real y, const real z);
		glm::vec3 getRotation() const;
		glm::mat4 getTransformationMatrix() const;
		void getInverseInertiaTensorWorld(glm::mat3* inverseInertiaTensorWorld) const;
		void addVelocity(const glm::vec3& deltaVelocity);
		void addRotation(const glm::vec3& deltaRotation);

		bool isDead();
		void setDead(const bool dead);


		// Löschen aller aufsummierten Kräfte und Drehmomente.
		void clearAccumulators();              
		// Hinzufügen einer Kraft in Weltkoordinaten.
		// Die Kraft muss am Schwerpunkt angreifen.
		// D'Allembert Prinzip.
		void addForce(const glm::vec3 & force); 
		// Hinzufügen einer Kraft in Weltkoordinaten.
		// Die Kraft wirkt in einem Punkt in Weltkoordinaten.
		// D'Allembert Prinzip.
		// Kraft kann auch Drehmoment bewirken.
		void addForceAtPoint(const glm::vec3 & force, const glm::vec3 & point);
		// Hinzufügen einer Kraft in Weltkoordinaten.
		// Die Kraft wirkt in einem Punkt in lokalen Körperkoordinaten.
		// D'Allembert Prinzip.
		void addForceAtBodyPoint(const glm::vec3 & force, const glm::vec3 & point);
		
		void addTorque(const glm::vec3 & torque); // Hinzufügen eines Drehmoments. D'Allembert Prinzip.

		glm::vec3 getPointInLocalSpace(const glm::vec3 &point) const;
		glm::vec3 getPointInWorldSpace(const glm::vec3 &point) const;
		glm::vec3 getDirectionInLocalSpace(const glm::vec3 &direction) const;
		glm::vec3 getDirectionInWorldSpace(const glm::vec3 &direction) const;

		glm::mat3 calculateCubeTensor(real mass, real x_half, real y_half, real z_half);
		glm::mat3 calculateShereTensor(real mass, real radius);

		virtual void integrate(real duration);// Bestimmung des neuen Ortes für das Teilchen.

	protected:
		real m_inverseMass;
		real m_linearDamping;
		real m_angularDamping;

		glm::vec3 m_position; // Position des Schwerpunkts. 
		glm::quat m_orientation;
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
		bool m_dead = false;

		void calculateTransformationMatrix(glm::mat4& transformationMatrix,
										   const glm::vec3& position,
										   const glm::quat& orientation);

		void transformInertiaTensor(glm::mat3& iitWorld,
									const glm::mat3& iit,
									const glm::mat4& rotMat);
	};
}

