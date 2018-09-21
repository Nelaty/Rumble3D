#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	Contact::Contact()
		: m_friction(0.5f),
		m_restitution(0.5f)
	{
	}

	Contact::~Contact()
	= default;

	RigidBody* Contact::getFirst() const
	{
		return m_pair.m_first;
	}

	RigidBody* Contact::getSecond() const
	{
		return m_pair.m_second;
	}

	RigidBody* Contact::getBody(const int index) const
	{
		assert(index == 0 || index == 1);

		return index == 0 ? m_pair.m_first : m_pair.m_second;
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
							  RigidBody* second,
	                          const real friction,
	                          const real restitution)
	{
		m_pair.m_first = first;
		m_pair.m_second = second;

		m_friction = friction;
		m_restitution = restitution;
	}

	real Contact::getFriction() const
	{
		return m_friction;
	}

	real Contact::getRestitution() const
	{
		return m_restitution;
	}

	glm::vec3 Contact::getContactVelocity() const
	{
		return m_contactVelocity;
	}

	void Contact::setContactVelocity(const glm::vec3& velocity)
	{
		m_contactVelocity = velocity;
	}

	real Contact::getDesiredDeltaVelocity() const
	{
		return m_desiredDeltaVelocity;
	}

	void Contact::calculateInternals(const real duration)
	{
		// Calculate an set of axis at the contact point.
		calculateContactBasis();

		const auto first = m_pair.m_first;
		const auto second = m_pair.m_second;

		// Store the relative position of the contact relative to each body
		m_relativeContactPosition[0] = m_contactPoint - first->getCenterOfMass();
		m_relativeContactPosition[1] = m_contactPoint - second->getCenterOfMass();

		// Find the relative velocity of the bodies at the contact point.
		m_contactVelocity = calculateLocalVelocity(0, duration);
		m_contactVelocity -= calculateLocalVelocity(1, duration);

		// Calculate the desired change in velocity for resolution
		calculateDesiredDeltaVelocity(duration);
	}

	glm::vec3 Contact::calculateLocalVelocity(const unsigned bodyIndex, real duration)
	{
		const auto thisBody = bodyIndex ? m_pair.m_second : m_pair.m_first;

		// Work out the velocity of the contact point.
		auto velocity = glm::cross(thisBody->getRotation(),
								   m_relativeContactPosition[bodyIndex]);
		velocity += thisBody->getVelocity();

		// Turn the velocity into contact-coordinates.
		// m_contactToWorld.transformTranspose(velocity);
		glm::vec3 contactVelocity = glm::transpose(m_contactToWorld) * velocity;

		return contactVelocity;

		/* Erst relevant, wenn lastFrame berücksichtigt wird.
		// Calculate the ammount of velocity that is due to forces without
		// reactions.
		glm::vec3 accVelocity = thisBody->getLastFrameAcceleration() * duration;

		// Calculate the velocity in contact-coordinates.
		accVelocity = contactToWorld.transformTranspose(accVelocity);

		// We ignore any component of acceleration in the contact normal
		// direction, we are only interested in planar acceleration
		accVelocity.x = 0;

		// Add the planar velocities - if there's enough friction they will
		// be removed during velocity resolution
		contactVelocity += accVelocity;

		// And return it
		return contactVelocity;
		*/
	}

	void Contact::calculateDesiredDeltaVelocity(const real duration)
	{
		/* Hier Code wenn isAwake implementiert und lastFrame verwendet wird:

		// Calculate the acceleration induced velocity accumulated this frame
		real velocityFromAcc = 0;

		if (body[0]->getAwake())
		{
		velocityFromAcc +=
		body[0]->getLastFrameAcceleration() * duration * contactNormal;
		}

		if (body[1] && body[1]->getAwake())
		{
		velocityFromAcc -=
		body[1]->getLastFrameAcceleration() * duration * contactNormal;
		}

		*/

		// If the velocity is very slow, limit the restitution
		auto thisRestitution = m_restitution;
		if(abs(m_contactVelocity.x) < s_velocityLimit)
		{
			thisRestitution = static_cast<real>(0.0f);
		}

		m_desiredDeltaVelocity =
			-m_contactVelocity.x
			- thisRestitution * m_contactVelocity.x; //- velocityFromAcc);


													 // -thisRestitution * m_contactVelocity.x - velocityFromAcc);
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

	void Contact::calculateContactBasis()
	{
		glm::vec3 contactTangent[2];
		const auto contactNormalX = m_contactNormal.x;
		const auto contactNormalY = m_contactNormal.y;
		const auto contactNormalZ = m_contactNormal.z;

		// Check whether the Z-axis is nearer to the X or Y axis
		if(abs(contactNormalX) > abs(contactNormalY))
		{
			// Scaling factor to ensure the results are normalized
			const auto s = static_cast<real>(1.0f) / sqrt(contactNormalZ*contactNormalZ +
														  contactNormalX * contactNormalX);

			// The new X-axis is at right angles to the world Y-axis
			contactTangent[0].x = s * contactNormalZ;
			contactTangent[0].y = 0;
			contactTangent[0].z = s * -contactNormalX;

			// The new Y-axis is at right angles to the new X- and Z- axes
			contactTangent[1].x = contactNormalY * contactTangent[0].x;
			contactTangent[1].y = contactNormalZ * contactTangent[0].x -
				contactNormalX * contactTangent[0].z;
			contactTangent[1].z = -contactNormalY * contactTangent[0].x;
		}
		else
		{
			// Scaling factor to ensure the results are normalized
			const real s = static_cast<real>(1.0) / sqrt(contactNormalZ*contactNormalZ +
														 contactNormalY * contactNormalY);

			// The new X-axis is at right angles to the world X-axis
			contactTangent[0].x = 0;
			contactTangent[0].y = s * -contactNormalZ;
			contactTangent[0].z = s * contactNormalY;

			// The new Y-axis is at right angles to the new X- and Z- axes
			contactTangent[1].x = contactNormalY * contactTangent[0].z -
				contactNormalZ * contactTangent[0].y;
			contactTangent[1].y = -contactNormalX * contactTangent[0].z;
			contactTangent[1].z = contactNormalX * contactTangent[0].y;
		}

		// Make a matrix from the three vectors.
		m_contactToWorld[0] = m_contactNormal;
		m_contactToWorld[1] = contactTangent[0];
		m_contactToWorld[2] = contactTangent[1];
	}
}
