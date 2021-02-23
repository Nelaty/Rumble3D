#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	Contact::Contact()
		: m_friction(0.5f),
		m_restitution(0.5f)
	{
	}

	RigidBody* Contact::getFirst() const
	{
		return m_pair.getFirst();
	}

	RigidBody* Contact::getSecond() const
	{
		return m_pair.getSecond();
	}

	RigidBody* Contact::getBody(const int index) const
	{
		return m_pair[index];
	}

	void Contact::setContactPoint(const glm::vec3& contactPoint)
	{
		m_contactPoint = contactPoint;
	}

	const glm::vec3& Contact::getContactPoint() const
	{
		return m_contactPoint;
	}

	void Contact::setContactNormal(const glm::vec3& contactNormal)
	{
		m_contactNormal = contactNormal;
	}

	glm::vec3 Contact::getContactNormal() const
	{
		return m_contactNormal;
	}

	void Contact::setPenetration(const real penetration)
	{
		m_penetration = penetration;
	}

	real Contact::getPenetration() const
	{
		return m_penetration;
	}

	void Contact::setBodyData(RigidBody* first,
							  RigidBody* second)
	{
		m_pair.init(first, second);
	
		m_friction = real(0.5) * (first->getPhysicsMaterial().getFriction() +
			second->getPhysicsMaterial().getFriction());
		m_restitution = real(0.5) * (first->getPhysicsMaterial().getRestitution() +
			second->getPhysicsMaterial().getRestitution());
	}

	real Contact::getFriction() const
	{
		return m_friction;
	}

	real Contact::getRestitution() const
	{
		return m_restitution;
	}

	glm::vec3 Contact::getClosingVelocity() const
	{
		return m_closingVelocity;
	}

	void Contact::setClosingVelocity(const glm::vec3& velocity)
	{
		m_closingVelocity = velocity;
	}

	real Contact::getDesiredDeltaVelocity() const
	{
		return m_desiredDeltaVelocity;
	}

	void Contact::calculateInternals(const real duration)
	{
		if(!m_pair.getFirst()->hasFiniteMass())
		{
			swapBodies();
		}
		// Calculate an set of axis at the contact point.
		calculateContactBasis();

		const auto first = m_pair.getFirst();
		const auto second = m_pair.getSecond();

		// Store the relative position of the contact relative to each body
		m_relativeContactPosition[0] = m_contactPoint - first->getCenterOfMass();
		if(second->hasFiniteMass())
		{
			m_relativeContactPosition[1] = m_contactPoint - second->getCenterOfMass();
		}
		
		// Find the relative velocity of the bodies at the contact point.
		m_closingVelocity = calculateLocalVelocity(0, duration);
		if(second->hasFiniteMass())
		{
			m_closingVelocity -= calculateLocalVelocity(1, duration);
		}

		// Calculate the desired change in velocity for resolution
		calculateDesiredDeltaVelocity(duration);
	}

	glm::vec3 Contact::calculateLocalVelocity(const unsigned bodyIndex,
											  const real duration)
	{
		const auto thisBody = m_pair[bodyIndex];

		// Work out the velocity of the contact point.
		auto velocity = glm::cross(thisBody->getRotation(),
								   m_relativeContactPosition[bodyIndex]);
		velocity += thisBody->getVelocity();

		// Turn the velocity into contact-coordinates.
		// m_contactToWorld.transformTranspose(velocity);
		auto contactVelocity = glm::transpose(m_contactToWorld) * velocity;

		// Calculate the ammount of velocity that is due to forces without
		// reactions.
		glm::vec3 accVelocity = thisBody->getLastFrameAcceleration() * duration;

		// Calculate the velocity in contact-coordinates.
		accVelocity = glm::transpose(m_contactToWorld) * accVelocity;

		// We ignore any component of acceleration in the contact normal
		// direction, we are only interested in planar acceleration
		accVelocity.x = 0;

		// Add the planar velocities - if there's enough friction they will
		// be removed during velocity resolution
		contactVelocity += accVelocity;

		// And return it
		return contactVelocity;
	}

	void Contact::calculateDesiredDeltaVelocity(const real duration)
	{
		auto first = m_pair.getFirst();
		auto second = m_pair.getSecond();

		// Calculate the acceleration induced velocity accumulated this frame
		real velocityFromAcc = 0;
		if (first->isAwake())
		{
			velocityFromAcc += duration *
				glm::dot(first->getLastFrameAcceleration(), m_contactNormal);
		}
		if(second->hasFiniteMass() && second->isAwake())
		{
			velocityFromAcc -= duration *
				glm::dot(second->getLastFrameAcceleration(), m_contactNormal);
		}

		// If the velocity is very slow, limit the restitution
		auto thisRestitution = m_restitution;
		if(abs(m_closingVelocity.x) < s_velocityLimit)
		{
			thisRestitution = 0;
		}

		m_desiredDeltaVelocity = 
			-m_closingVelocity.x -
			thisRestitution * (m_closingVelocity.x - velocityFromAcc);
	}

	const glm::vec3& Contact::getRelativeContactPosition(const int index) const
	{
		assert(index == 0 || index == 1);

		return m_relativeContactPosition[index];
	}

	const glm::mat3& Contact::getContactToWorld() const
	{
		return m_contactToWorld;
	}

	void Contact::matchAwakeState()
	{
		if(m_pair.getSecond()->hasFiniteMass())
		{
			return;
		}

		auto first = m_pair.getFirst();
		auto second = m_pair.getSecond();

		if(first->isAwake() || second->isAwake())
		{
			m_pair.getFirst()->setAwake(true);
			m_pair.getSecond()->setAwake(true);
		}
	}

	void Contact::calculateContactBasis()
	{
		glm::vec3 contactTangent[2]{};
		const auto contactNormalX = m_contactNormal.x;
		const auto contactNormalY = m_contactNormal.y;
		const auto contactNormalZ = m_contactNormal.z;

		// Check whether the Z-axis is nearer to the X or Y axis
		if(abs(contactNormalX) > abs(contactNormalY))
		{
			// Scaling factor to ensure the results are normalized
			const auto s = real(1) / sqrt(contactNormalZ * contactNormalZ +
										  contactNormalX * contactNormalX);

			// The new X-axis is at right angles to the world Y-axis
			contactTangent[0].x = s * contactNormalZ;
			contactTangent[0].y = 0;
			contactTangent[0].z = s * -contactNormalX;

			// The new Y-axis is at right angles to the new X- and Z- axes
			contactTangent[1].x = contactNormalY * contactTangent[0].x;
			contactTangent[1].y = 
				contactNormalZ * contactTangent[0].x -
				contactNormalX * contactTangent[0].z;
			contactTangent[1].z = -contactNormalY * contactTangent[0].x;
		}
		else
		{
			// Scaling factor to ensure the results are normalized
			const real s = real(1) / sqrt(contactNormalZ * contactNormalZ +
										  contactNormalY * contactNormalY);

			// The new X-axis is at right angles to the world X-axis
			contactTangent[0].x = 0;
			contactTangent[0].y = s * -contactNormalZ;
			contactTangent[0].z = s * contactNormalY;

			// The new Y-axis is at right angles to the new X- and Z- axes
			contactTangent[1].x = 
				contactNormalY * contactTangent[0].z - 
				contactNormalZ * contactTangent[0].y;
			contactTangent[1].y = -contactNormalX * contactTangent[0].z;
			contactTangent[1].z = contactNormalX * contactTangent[0].y;
		}

		// Make a matrix from the three vectors.
		m_contactToWorld[0] = m_contactNormal;
		m_contactToWorld[1] = contactTangent[0];
		m_contactToWorld[2] = contactTangent[1];
	}

	void Contact::swapBodies()
	{
		m_contactNormal *= -1;
		m_pair.swapBodies();
	}
}
