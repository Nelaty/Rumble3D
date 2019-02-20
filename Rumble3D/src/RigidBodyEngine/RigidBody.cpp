#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/PhysicsMaterial.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

#include <cassert>
#include <glm/gtc/matrix_transform.inl>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace r3
{
	RigidBody::RigidBody()
	{
		init(RigidBodyDef());
	}

	RigidBody::RigidBody(const RigidBodyDef& def)
	{
		init(def);
	}

	RigidBody::~RigidBody()
	= default;

	void RigidBody::init(const RigidBodyDef& definition)
	{
		m_physicsMaterial = definition.m_physicsMaterial;
		m_collisionMask = definition.m_collisionMask;
		m_collisionPrimitive = definition.m_collisionPrimitive;

		setInverseMass(definition.m_inverseMass);

		m_linearDamping = definition.m_linearDamping;
		m_angularDamping = definition.m_angularDamping;

		m_velocity = definition.m_velocity;
		m_acceleration = definition.m_acceleration;
		m_lastFrameAcceleration = definition.m_lastFrameAcceleration;
		m_rotation = definition.m_rotation;

		m_inverseInertiaTensor = definition.m_inverseInertiaTensor;
		m_inverseInertiaTensorWorld = definition.m_inverseInertiaTensorWorld;

		m_forceAccumulated = definition.m_forceAccumulated;
		m_torqueAccumulated = definition.m_torqueAccumulated;
		m_awake = definition.m_awake;

		m_motion = 0;
		m_sleepEpsilon = real(0.3);
		m_canSleep = false;
	}

	void RigidBody::calculateTransformationMatrix(glm::mat4& transformationMatrix,
	                                              const glm::vec3& position,
	                                              const glm::mat3& orientation)
	{
		transformationMatrix = orientation;
		transformationMatrix = glm::translate(transformationMatrix, position);
	}

	void RigidBody::transformInertiaTensor(glm::mat3& iitWorld,
	                                       const glm::mat3& iit,
	                                       const glm::mat4& rotMat)
	{
		// Same as Millington, but readable
		const glm::mat3 rot = rotMat;
		iitWorld = rot * iit * glm::transpose(rot);

		// Der folgende Code wurde von Millington direkt übernommen,
		// der behauptet, er wäre automatisch optimiert worden:		
		/*real t4 = 
			rotMat[0][0] * iit[0][0] +
			rotMat[1][0] * iit[0][1] +
			rotMat[2][0] * iit[0][2];
		real t9 = 
			rotMat[0][0] * iit[1][0] +
			rotMat[1][0] * iit[1][1] +
			rotMat[2][0] * iit[1][2];
		real t14 = 
			rotMat[0][0] * iit[2][0] +
			rotMat[1][0] * iit[2][1] +
			rotMat[2][0] * iit[2][2];
		real t28 = 
			rotMat[0][1] * iit[0][0] +
			rotMat[1][1] * iit[0][1] +
			rotMat[2][1] * iit[0][2];
		real t33 = 
			rotMat[0][1] * iit[1][0] +
			rotMat[1][1] * iit[1][1] +
			rotMat[2][1] * iit[1][2];
		real t38 = 
			rotMat[0][1] * iit[2][0] +
			rotMat[1][1] * iit[2][1] +
			rotMat[2][1] * iit[2][2];
		real t52 = 
			rotMat[0][2] * iit[0][0] +
			rotMat[1][2] * iit[0][1] +
			rotMat[2][2] * iit[0][2];
		real t57 = 
			rotMat[0][2] * iit[1][0] +
			rotMat[1][2] * iit[1][1] +
			rotMat[2][2] * iit[1][2];
		real t62 = 
			rotMat[0][2] * iit[2][0] +
			rotMat[1][2] * iit[2][1] +
			rotMat[2][2] * iit[2][2];


		iitWorld[0][0] = 
			t4 * rotMat[0][0] +
			t9 * rotMat[1][0] +
			t14 * rotMat[2][0];
		iitWorld[1][0] =
			t4 * rotMat[0][1] +
			t9 * rotMat[1][1] +
			t14 * rotMat[2][1];
		iitWorld[2][0] =
			t4 * rotMat[0][2] +
			t9 * rotMat[1][2] +
			t14 * rotMat[2][2];
		iitWorld[0][1] = 
			t28 * rotMat[0][0] +
			t33 * rotMat[1][0] +
			t38 * rotMat[2][0];
		iitWorld[1][1] = 
			t28 * rotMat[0][1] +
			t33 * rotMat[1][1] +
			t38 * rotMat[2][1];
		iitWorld[2][1] = 
			t28 * rotMat[0][2] +
			t33 * rotMat[1][2] +
			t38 * rotMat[2][2];
		iitWorld[0][2] = 
			t52 * rotMat[0][0] +
			t57 * rotMat[1][0] +
			t62 * rotMat[2][0];
		iitWorld[1][2] = 
			t52 * rotMat[0][1] +
			t57 * rotMat[1][1] +
			t62 * rotMat[2][1];
		iitWorld[2][2] = 
			t52 * rotMat[0][2] +
			t57 * rotMat[1][2] +
			t62 * rotMat[2][2];*/
	}

	glm::vec3 RigidBody::getPointInLocalSpace(const glm::vec3& point) const
	{
		return m_transform.getPointInLocalSpace(point);
	}

	glm::vec3 RigidBody::getPointInWorldSpace(const glm::vec3& point) const
	{
		return m_transform.getPointInWorldSpace(point);
	}

	glm::vec3 RigidBody::getDirectionInLocalSpace(const glm::vec3& direction) const
	{
		return m_transform.getDirectionInLocalSpace(direction);
	}

	glm::vec3 RigidBody::getDirectionInWorldSpace(const glm::vec3& direction) const
	{
		return m_transform.getDirectionInWorldSpace(direction);
	}

	void RigidBody::calculateDerivedData()
	{
		auto orientation = m_transform.getRotationMat();
		//orientation = glm::normalize(orientation);
		calculateTransformationMatrix(m_transformationMatrix, m_transform.getPosition(), orientation);
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
		assert(mass > 0.0f);
		m_mass = mass;
		m_inverseMass = real(1) / mass;
	}

	real RigidBody::getMass() const
	{
		return m_mass;
	}

	void RigidBody::setInverseMass(const real inverseMass)
	{
		m_mass = inverseMass != real(0) ? real(1) / inverseMass : R3D_REAL_MAX;
		m_inverseMass = inverseMass;
	}

	real RigidBody::getInverseMass() const
	{
		return m_inverseMass;
	}

	bool RigidBody::hasFiniteMass() const
	{
		return m_inverseMass > real(0);
	}

	glm::vec3 RigidBody::getForceAccumulated() const
	{
		return m_forceAccumulated;
	}

	glm::vec3 RigidBody::getTorqueAccumulated() const
	{
		return m_torqueAccumulated;
	}

	const glm::vec3& RigidBody::getLastFrameAcceleration() const
	{
		return m_lastFrameAcceleration;
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

	real RigidBody::getAngularDamping() const
	{
		return m_angularDamping;
	}

	void RigidBody::setCenterOfMass(const glm::vec3& centerOfMass)
	{
		m_transform.setPosition(centerOfMass);
	}

	void RigidBody::setCenterOfMass(const real x, const real y, const real z)
	{
		m_transform.setPosition(x, y, z);
	}

	glm::vec3 RigidBody::getCenterOfMass() const
	{
		return m_transform.getPosition();
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

	const glm::mat3& RigidBody::getInverseInertiaTensorWorld() const
	{
		return m_inverseInertiaTensorWorld;
	}

	const glm::vec3& RigidBody::getAcceleration() const
	{
		return m_acceleration;
	}

	void RigidBody::setOrientation(const glm::quat& orientation)
	{
		m_transform.setRotation(orientation);
	}

	void RigidBody::setOrientation(const real r, const real i, const real j, const real k)
	{
		m_transform.setRotation(r, i, j, k);
	}

	glm::quat RigidBody::getOrientation() const
	{
		return glm::quat_cast(m_transform.getRotationMat());
	}

	void RigidBody::setRotation(const glm::vec3& rotation)
	{
		m_rotation = rotation;
	}

	void RigidBody::setRotation(const real x, const real y, const real z)
	{
		m_rotation = glm::vec3(x, y, z);
	}

	glm::vec3 RigidBody::getRotation() const
	{
		return m_rotation;
	}

	bool RigidBody::isAwake() const
	{
		return m_awake;
	}

	void RigidBody::setAwake(const bool awake)
	{
		m_awake = awake;
		if(awake)
		{
			m_motion = m_sleepEpsilon * 2.0f;
		}
		else
		{
			m_velocity = glm::vec3(0);
			m_rotation = glm::vec3(0);
		}
	}

	bool RigidBody::canSleep() const
	{
		return m_canSleep;
	}

	void RigidBody::setCanSleep(const bool canSleep)
	{
		m_canSleep = canSleep;

		if(!m_canSleep)
		{
			setAwake(true);
		}
	}

	void RigidBody::setPhysicsMaterial(const PhysicsMaterial& material)
	{
		m_physicsMaterial = material;
	}

	const PhysicsMaterial& RigidBody::getPhysicsMaterial() const
	{
		return m_physicsMaterial;
	}

	void RigidBody::clearAccumulators()
	{
		m_forceAccumulated = glm::vec3(0);
		m_torqueAccumulated = glm::vec3(0);
	}

	void RigidBody::addForce(const glm::vec3& force)
	{
		m_forceAccumulated += force;
	}

	void RigidBody::addForceAtPoint(const glm::vec3& force, const glm::vec3& point)
	{
		// Angriffspunkt der Kraft relativ zum Schwerpunkt:
		const auto pointLocal = point - m_transform.getPosition();
		
		m_forceAccumulated += force;
		m_torqueAccumulated += cross(pointLocal, force);
	}

	void RigidBody::addForceAtBodyPoint(const glm::vec3& force, const glm::vec3& point)
	{
		const auto pointWorld = getPointInWorldSpace(point);
		addForceAtPoint(force, pointWorld);
	}

	void RigidBody::addTorque(const glm::vec3& torque)
	{
		m_torqueAccumulated += torque;
	}

	void RigidBody::setCollisionCallback(const CollisionCallback& callback)
	{
		m_collisionCallback = callback;
	}

	const CollisionCallback& RigidBody::getCollisionCallback() const
	{
		return m_collisionCallback;
	}

	const glm::mat4& RigidBody::getTransformationMatrix() const
	{
		return m_transformationMatrix;
	}

	void RigidBody::integrate(const real timeDelta)
	{
		if(!m_awake) return;

		calculateDerivedData();

		// Linear acceleration
		m_lastFrameAcceleration = m_acceleration;
		m_lastFrameAcceleration += m_inverseMass * m_forceAccumulated;

		// Angular acceleration from torque
		const auto angularAcceleration = m_inverseInertiaTensorWorld * m_torqueAccumulated;

		// Linear velocity from velocity and impulse
		m_velocity += timeDelta * m_lastFrameAcceleration;

		// Angular velocity from angular acceleration and impulse
		m_rotation += timeDelta * angularAcceleration;

		// Drag
		m_velocity *= pow(m_linearDamping, timeDelta);
		m_rotation *= pow(m_angularDamping, timeDelta);
	
		// Linear position update
		m_transform.translate(timeDelta * m_velocity);

		// Rotational position update
		m_transform.updateOrientationByAngularVelocity(m_rotation, timeDelta);

		// Normalize orientation and update derived data
		calculateDerivedData();

		clearAccumulators();

		if(m_canSleep)
		{
			real currentMotion = 
				glm::dot(m_velocity, m_velocity) +
				glm::dot(m_rotation, m_rotation);

			real bias = pow(real(0.5), timeDelta);
			m_motion = bias * m_motion + (real(1) - bias)*currentMotion;

			if(m_motion < m_sleepEpsilon)
			{
				setAwake(false);
			}
			else if(m_motion > real(10) * m_sleepEpsilon)
			{
				m_motion = real(10) * m_sleepEpsilon;
			}
		}
	}

	void RigidBody::reset(const glm::vec3& position,
						  const glm::vec3& rotation)
	{
		m_velocity = glm::vec3(0);
		m_acceleration = glm::vec3(0);
		m_lastFrameAcceleration = glm::vec3(0);
		m_rotation = glm::vec3(0);

		m_transform.reset(position, rotation);
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


#undef GLM_ENABLE_EXPERIMENTAL