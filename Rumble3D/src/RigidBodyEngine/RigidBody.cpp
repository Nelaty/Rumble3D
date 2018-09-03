#include "R3D/RigidBodyEngine/RigidBody.h"
#include <cassert>

#include "R3D/RigidBodyEngine/CollisionPrimitive.h"


namespace r3
{
	void RigidBody::calculateTransformationMatrix(glm::mat4& transformationMatrix,
												  const glm::vec3& position,
												  const glm::quat& orientation)
	{
		transformationMatrix = glm::mat4_cast(orientation);
		transformationMatrix[3] += glm::vec4(position, static_cast<real>(1.0f));
	}
	
	void RigidBody::transformInertiaTensor(glm::mat3& iitWorld,
										   const glm::mat3& iit,
										   const glm::mat4& rotMat)
	{

		// Der folgende Code wurde von Millington direkt übernommen,
		// der behauptet, er wäre automatisch optimiert worden:
		/*
		real t4 = rotMat.m00 * iit.m00 +
			rotMat.m01 * iit.m10 +
			rotMat.m02 * iit.m20;
		real t9 = rotMat.m00 * iit.m01 +
			rotMat.m01 * iit.m11 +
			rotMat.m02 * iit.m21;
		real t14 = rotMat.m00 * iit.m02 +
			rotMat.m01 * iit.m12 +
			rotMat.m02 * iit.m22;
		real t28 = rotMat.m10 * iit.m00 +
			rotMat.m11 * iit.m10 +
			rotMat.m12 * iit.m20;
		real t33 = rotMat.m10 * iit.m01 +
			rotMat.m11 * iit.m11 +
			rotMat.m12 * iit.m21;
		real t38 = rotMat.m10 * iit.m02 +
			rotMat.m11 * iit.m12 +
			rotMat.m12 * iit.m22;
		real t52 = rotMat.m20 * iit.m00 +
			rotMat.m21 * iit.m10 +
			rotMat.m22 * iit.m20;
		real t57 = rotMat.m20 * iit.m01 +
			rotMat.m21 * iit.m11 +
			rotMat.m22 * iit.m21;
		real t62 = rotMat.m20 * iit.m02 +
			rotMat.m21 * iit.m12 +
			rotMat.m22 * iit.m22;
		*/
		
		real t4 = rotMat[0][0] *iit[0][0] +
			rotMat[1][0] * iit[0][1] +
			rotMat[2][0] * iit[0][2];
		real t9 = rotMat[0][0] * iit[1][0] +
			rotMat[1][0] * iit[1][1] +
			rotMat[2][0] * iit[1][2];
		real t14 = rotMat[0][0] * iit[2][0] +
			rotMat[1][0] * iit[2][1] +
			rotMat[2][0] * iit[2][2];
		real t28 = rotMat[0][1] * iit[0][0] +
			rotMat[1][1] * iit[0][1] +
			rotMat[2][1] * iit[0][2];
		real t33 = rotMat[0][1] * iit[1][0] +
			rotMat[1][1] * iit[1][1] +
			rotMat[2][1] * iit[1][2];
		real t38 = rotMat[0][1] * iit[2][0] +
			rotMat[1][1] * iit[2][1] +
			rotMat[2][1] * iit[2][2];
		real t52 = rotMat[0][2] * iit[0][0] +
			rotMat[1][2] * iit[0][1] +
			rotMat[2][2] * iit[0][2];
		real t57 = rotMat[0][2] * iit[1][0] +
			rotMat[1][2] * iit[1][1] +
			rotMat[2][2] * iit[1][2];
		real t62 = rotMat[0][2] * iit[2][0] +
			rotMat[1][2] * iit[2][1] +
			rotMat[2][2] * iit[2][2];
		
		/*
		iitWorld.m00 = t4*rotMat.m00 +
			t9*rotMat.m01 +
			t14*rotMat.m02;
		iitWorld.m01 = t4*rotMat.m10 +
			t9*rotMat.m11 +
			t14*rotMat.m12;
		iitWorld.m02 = t4*rotMat.m20 +
			t9*rotMat.m21 +
			t14*rotMat.m22;
		iitWorld.m10 = t28*rotMat.m00 +
			t33*rotMat.m01 +
			t38*rotMat.m02;
		iitWorld.m11 = t28*rotMat.m10 +
			t33*rotMat.m11 +
			t38*rotMat.m12;
		iitWorld.m12 = t28*rotMat.m20 +
			t33*rotMat.m21 +
			t38*rotMat.m22;
		iitWorld.m20 = t52*rotMat.m00 +
			t57*rotMat.m01 +
			t62*rotMat.m02;
		iitWorld.m21 = t52*rotMat.m10 +
			t57*rotMat.m11 +
			t62*rotMat.m12;
		iitWorld.m22 = t52*rotMat.m20 +
			t57*rotMat.m21 +
			t62*rotMat.m22;
		*/

		iitWorld[0][0] = t4*rotMat[0][0] +
			t9*rotMat[1][0] +
			t14*rotMat[2][0];
		iitWorld[1][0] = t4*rotMat[0][1] +
			t9*rotMat[1][1] +
			t14*rotMat[2][1];
		iitWorld[2][0] = t4*rotMat[0][2] +
			t9*rotMat[1][2] +
			t14*rotMat[2][2];
		iitWorld[0][1] = t28*rotMat[0][0] +
			t33*rotMat[1][0] +
			t38*rotMat[2][0];
		iitWorld[1][1] = t28*rotMat[0][1] +
			t33*rotMat[1][1] +
			t38*rotMat[2][1];
		iitWorld[2][1] = t28*rotMat[0][2] +
			t33*rotMat[1][2] +
			t38*rotMat[2][2];
		iitWorld[0][2] = t52*rotMat[0][0] +
			t57*rotMat[1][0] +
			t62*rotMat[2][0];
		iitWorld[1][2] = t52*rotMat[0][1] +
			t57*rotMat[1][1] +
			t62*rotMat[2][1];
		iitWorld[2][2] = t52*rotMat[0][2] +
			t57*rotMat[1][2] +
			t62*rotMat[2][2];
	}
	
	glm::vec3 RigidBody::getPointInLocalSpace(const glm::vec3& point) const
	{
		// return m_transformationMatrix.transformInverse(point);
	
		glm::vec3 temp = point;
		temp -= glm::vec3(m_transformationMatrix[3]);
		return glm::inverse(glm::mat3(m_transformationMatrix)) * temp;
	}
	
	glm::vec3 RigidBody::getPointInWorldSpace(const glm::vec3& point) const
	{
		return glm::vec3(m_transformationMatrix * glm::vec4(point, static_cast<real>(1.0f)));
	}
	
	glm::vec3 RigidBody::getDirectionInLocalSpace(const glm::vec3& direction) const
	{
		// return m_transformationMatrix.transformInverseDirection(direction);
		return glm::inverse(glm::mat3(m_transformationMatrix)) * direction;
	}
	
	glm::vec3 RigidBody::getDirectionInWorldSpace(const glm::vec3& direction) const
	{
		return glm::mat3(m_transformationMatrix) * direction;
	}

	RigidBody::RigidBody()
	= default;

	RigidBody::~RigidBody()
	= default;

	void RigidBody::calculateDerivedData()
	{
		m_orientation = glm::normalize(m_orientation);
		calculateTransformationMatrix(m_transformationMatrix, m_centerOfMass, m_orientation);
		transformInertiaTensor(m_inverseInertiaTensorWorld,
							   m_inverseInertiaTensor,
							   m_transformationMatrix);
	}
	
	void RigidBody::setInertiaTensor(const glm::mat3& inertiaTensor)
	{
		m_inverseInertiaTensor = glm::inverse(inertiaTensor);
	}
	
	glm::mat3 RigidBody::getInverseTensor() const
	{
		return m_inverseInertiaTensor;
	}
	
	void RigidBody::setMass(const real mass)
	{
		assert(mass != 0);
		m_inverseMass = static_cast<real>(1.0f) / mass;
	}
	
	real RigidBody::getMass() const
	{
		if (m_inverseMass == 0) 
		{
			return R3D_REAL_MAX;
		}
		return static_cast<real>(1.0f) / m_inverseMass;
	}
	
	void RigidBody::setInverseMass(const real inverseMass)
	{
		m_inverseMass = inverseMass;
	}
	
	real RigidBody::getInverseMass() const
	{
		return m_inverseMass;
	}
	
	bool RigidBody::hasFiniteMass() const
	{
		return m_inverseMass > 0.0f;
	}
	
	glm::vec3 RigidBody::getForceAccumulated() const
	{
		return m_forceAccumulated;
	}
	
	glm::vec3 RigidBody::getTorqueAccumulated() const
	{
		return m_torqueAccumulated;
	}
	
	void RigidBody::setLinearDamping(const real linearDamping)
	{
		m_linearDamping = linearDamping;
	}
	
	real RigidBody::getLinearDamping() const
	{
		return m_linearDamping;
	}
	
	void RigidBody::setAngularDamping(const real angularDamping)
	{
		m_angularDamping = angularDamping;
	}
	
	real RigidBody::getAngularDamping() const{
		return m_angularDamping;
	}
	
	void RigidBody::setCenterOfMass(const glm::vec3& centerOfMass)
	{
		m_centerOfMass = centerOfMass;
	}
	
	void RigidBody::setCenterOfMass(const real x, const real y, const real z)
	{
		m_centerOfMass.x = x;
		m_centerOfMass.y = y;
		m_centerOfMass.z = z;
	}
	
	glm::vec3 RigidBody::getCenterOfMass() const
	{
		return m_centerOfMass;
	}
	
	void RigidBody::setVelocity(const glm::vec3& velocity)
	{
		m_velocity = velocity;
	}
	
	void RigidBody::setVelocity(const real x, const real y, const real z)
	{
		m_velocity.x = x;
		m_velocity.y = y;
		m_velocity.z = z;
	}
	
	glm::vec3 RigidBody::getVelocity() const
	{
		return m_velocity;
	}
	
	void RigidBody::setAcceleration(const glm::vec3& acceleration)
	{
		m_acceleration = acceleration;
	}
	
	void RigidBody::setAcceleration(const real x, const real y, const real z)
	{
		m_acceleration.x = x;
		m_acceleration.y = y;
		m_acceleration.z = z;
	}
	
	void RigidBody::getInverseInertiaTensorWorld(glm::mat3* inverseInertiaTensorWorld) const 
	{
		*inverseInertiaTensorWorld = m_inverseInertiaTensorWorld;
	}
	
	glm::vec3 RigidBody::getAcceleration() const
	{
		return m_acceleration;
	}
	
	void RigidBody::setOrientation(const glm::quat & orientation)
	{
		m_orientation = orientation;
	}
	
	void RigidBody::setOrientation(const real r, const real i, const real j, const real k)
	{
		m_orientation.w = r;
		m_orientation.x = i;
		m_orientation.y = j;
		m_orientation.z = k;
	}
	
	glm::quat RigidBody::getOrientation() const
	{
		return m_orientation;
	}
	
	void RigidBody::setRotation(const glm::vec3 & rotation)
	{
		m_rotation = rotation;
	}
	
	void RigidBody::setRotation(const real x, const real y, const real z)
	{
		m_rotation = glm::vec3(x,y,z);
	}
	
	glm::vec3 RigidBody::getRotation() const
	{
		return m_rotation;
	}
	
	bool RigidBody::isDead() const
	{
		return m_dead;
	}
	
	void RigidBody::setDead(const bool dead)
	{
		m_dead = dead;
	}
	
	void RigidBody::clearAccumulators()
	{
		m_forceAccumulated = glm::vec3(static_cast<real>(0.0f));
		m_torqueAccumulated = glm::vec3(static_cast<real>(0.0f));
	}
	
	void RigidBody::addForce(const glm::vec3& force)
	{
		m_forceAccumulated += force;
	}
	
	void RigidBody::addForceAtPoint(const glm::vec3& force, const glm::vec3& point)
	{
		// Angriffspunkt der Kraft relativ zum Schwerpunkt:
		auto pt = point;
		pt -= m_centerOfMass;
	
		m_forceAccumulated += force;
		m_torqueAccumulated += glm::cross(pt, force);
	}
	
	void RigidBody::addForceAtBodyPoint(const glm::vec3& force, const glm::vec3& point)
	{
		const auto pt = getPointInWorldSpace(point);
		addForceAtPoint(force, pt);
	}
	
	void RigidBody::addTorque(const glm::vec3 &torque)
	{
		m_torqueAccumulated += torque;
	}
	
	glm::mat4 RigidBody::getTransformationMatrix() const
	{
		return m_transformationMatrix;
	}
	
	void RigidBody::integrate(const real duration) 
	{
		calculateDerivedData();
		// Lineare Beschleunigung:
		m_lastFrameAcceleration = m_acceleration;
		m_lastFrameAcceleration += m_inverseMass * m_forceAccumulated;

		// Winkelbeschleunigung aus Drehmoment:
		glm::vec3 angularAcceleration = m_inverseInertiaTensorWorld * m_torqueAccumulated;
			
		// Lineare Geschwindigkeit aus Beschleunigung und Impuls:
		m_velocity += duration * m_lastFrameAcceleration;

		// Winkelgeschwindigkeit aus Winkelbeschleunigung und Impuls:
		m_rotation += duration * angularAcceleration;

		// Dämpfung:
		m_velocity *= pow(m_linearDamping, duration);
		m_rotation *= pow(m_angularDamping, duration);
		m_rotation *= static_cast<real>(-1.0f); //Da Rotation falsch herum in Vektoria
	
		// Positionsanpassung linear:
		m_centerOfMass += duration * m_velocity;
		
		// Positionsanpassung Drehung:
		//m_orientation.updateOrientationByAngularVelocity(m_rotation, duration);		
		m_orientation += (glm::quat(0, m_rotation * duration) * m_orientation) * static_cast<real>(0.5f);

		// Normalisierung der Orientierung und Update der abgeleiteten Daten:
		calculateDerivedData();
	
		clearAccumulators();
		m_rotation *= -1.0; //Wieder zurückrechnen. Da Rotation falsch herum in Vektoria
	}
	
	void RigidBody::addVelocity(const glm::vec3& deltaVelocity)
	{
		m_velocity += deltaVelocity;
	}
	
	void RigidBody::addRotation(const glm::vec3& deltaRotation)
	{
		m_rotation += deltaRotation;
	}
}