#include "R3D/RigidBodyEngine/RigidBody.h"
#include "R3D/RigidBodyEngine/PhysicsMaterial.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

#include <cassert>
#include <glm/gtc/matrix_transform.inl>

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
	}

	void RigidBody::calculateTransformationMatrix(glm::mat4& transformationMatrix,
	                                              const glm::vec3& position,
	                                              const glm::mat3& orientation)
	{
		transformationMatrix = orientation;
		transformationMatrix = glm::translate(transformationMatrix, position);

		//transformationMatrix[3] += glm::vec4(position, static_cast<real>(1.0f));
	}

	void RigidBody::transformInertiaTensor(glm::mat3& iitWorld,
	                                       const glm::mat3& iit,
	                                       const glm::mat4& rotMat)
	{
		/// \todo: refactor
		// Der folgende Code wurde von Millington direkt übernommen,
		// der behauptet, er wäre automatisch optimiert worden:		
		real t4 = rotMat[0][0] * iit[0][0] +
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


		iitWorld[0][0] = t4 * rotMat[0][0] +
			t9 * rotMat[1][0] +
			t14 * rotMat[2][0];
		iitWorld[1][0] = t4 * rotMat[0][1] +
			t9 * rotMat[1][1] +
			t14 * rotMat[2][1];
		iitWorld[2][0] = t4 * rotMat[0][2] +
			t9 * rotMat[1][2] +
			t14 * rotMat[2][2];
		iitWorld[0][1] = t28 * rotMat[0][0] +
			t33 * rotMat[1][0] +
			t38 * rotMat[2][0];
		iitWorld[1][1] = t28 * rotMat[0][1] +
			t33 * rotMat[1][1] +
			t38 * rotMat[2][1];
		iitWorld[2][1] = t28 * rotMat[0][2] +
			t33 * rotMat[1][2] +
			t38 * rotMat[2][2];
		iitWorld[0][2] = t52 * rotMat[0][0] +
			t57 * rotMat[1][0] +
			t62 * rotMat[2][0];
		iitWorld[1][2] = t52 * rotMat[0][1] +
			t57 * rotMat[1][1] +
			t62 * rotMat[2][1];
		iitWorld[2][2] = t52 * rotMat[0][2] +
			t57 * rotMat[1][2] +
			t62 * rotMat[2][2];
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
		const auto orientation = m_transform.getRotation();
		calculateTransformationMatrix(m_transformationMatrix, m_transform.getPosition(), orientation);
		transformInertiaTensor(m_inverseInertiaTensorWorld,
		                       m_inverseInertiaTensor,
		                       m_transformationMatrix);
	}

	void RigidBody::setInertiaTensor(const glm::mat3& inertiaTensor)
	{
		m_inverseInertiaTensor = inverse(inertiaTensor);
	}

	glm::mat3 RigidBody::getInverseTensor() const
	{
		return m_inverseInertiaTensor;
	}

	void RigidBody::setMass(const real mass)
	{
		assert(mass > 0.0f);
		m_mass = mass;
		m_inverseMass = static_cast<real>(1.0f) / mass;
	}

	real RigidBody::getMass() const
	{
		return m_mass;
	}

	void RigidBody::setInverseMass(const real inverseMass)
	{
		m_mass = inverseMass != 0.0f ? 1.0f / inverseMass : R3D_REAL_MAX;
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

	glm::vec3 RigidBody::getAcceleration() const
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
		return glm::quat_cast(m_transform.getRotation());
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
	}

	void RigidBody::setPhysicsMaterial(PhysicsMaterial* material)
	{
		m_physicsMaterial = material;
	}

	PhysicsMaterial* RigidBody::getPhysicsMaterial() const
	{
		return m_physicsMaterial;
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
		const auto pt = point - m_transform.getPosition();
		
		m_forceAccumulated += force;
		m_torqueAccumulated += cross(pt, force);
	}

	void RigidBody::addForceAtBodyPoint(const glm::vec3& force, const glm::vec3& point)
	{
		const auto pt = getPointInWorldSpace(point);
		addForceAtPoint(force, pt);
	}

	void RigidBody::addTorque(const glm::vec3& torque)
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
		const auto angularAcceleration = m_inverseMass * m_inverseInertiaTensorWorld * m_torqueAccumulated;

		// Lineare Geschwindigkeit aus Beschleunigung und Impuls:
		m_velocity += duration * m_lastFrameAcceleration;

		// Winkelgeschwindigkeit aus Winkelbeschleunigung und Impuls:
		m_rotation += duration * angularAcceleration;

		// Dämpfung:
		m_velocity *= pow(m_linearDamping, duration);
		m_rotation *= pow(m_angularDamping, duration);
		m_rotation *= static_cast<real>(-1.0f); //Da Rotation falsch herum in Vektoria

		// Positionsanpassung linear:
		m_transform.translate(duration * m_velocity);

		// Positionsanpassung Drehung:
		//m_orientation.updateOrientationByAngularVelocity(m_rotation, duration);		
		m_transform.rotate((glm::quat(0, m_rotation * duration) * glm::quat_cast(m_transform.getRotation())) * static_cast<real>(0.5f));

		// Normalisierung der Orientierung und Update der abgeleiteten Daten:
		calculateDerivedData();

		clearAccumulators();
		//m_rotation *= -1.0; //Wieder zurückrechnen. Da Rotation falsch herum in Vektoria
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
