#include "R3D/RigidBodyEngine/ContactResolver.h"
#include "R3D/RigidBodyEngine/Contact.h"

#include <glm/glm.hpp>

namespace rum
{
	
	ContactResolver::ContactResolver(unsigned iterations,
									 real velocityEpsilon,
									 real positionEpsilon)
	{
		setIterations(iterations, iterations);
		setEpsilon(velocityEpsilon, positionEpsilon);
	}
	
	ContactResolver::ContactResolver(unsigned velocityIterations,
									 unsigned positionIterations,
									 real velocityEpsilon,
									 real positionEpsilon)
	{
		setIterations(velocityIterations);
		setEpsilon(velocityEpsilon, positionEpsilon);
	}
	
	void ContactResolver::setIterations(unsigned iterations)
	{
		setIterations(iterations, iterations);
	}
	
	void ContactResolver::setIterations(unsigned velocityIterations,
										unsigned positionIterations)
	{
		m_velocityIterations = velocityIterations;
		m_positionIterations = positionIterations;
	}
	
	void ContactResolver::setEpsilon(real velocityEpsilon,
									 real positionEpsilon)
	{
		m_velocityEpsilon = velocityEpsilon;
		m_positionEpsilon = positionEpsilon;
	}
	
	void ContactResolver::resolveContacts(Contact *contacts,
										  unsigned numContacts,
										  real duration)
	{
		// Make sure we have something to do.
		if(numContacts == 0)
		{
			return;
		}
		if(!isValid())
		{
			return;
		}
		// Prepare the contacts for processing
		prepareContacts(contacts, numContacts, duration);
	
		// Resolve the interpenetration problems with the contacts.
		adjustPositions(contacts, numContacts, duration);
	
		// Resolve the velocity problems with the contacts.
		adjustVelocities(contacts, numContacts, duration);
	}
	
	void ContactResolver::prepareContacts(Contact* contacts,
										  unsigned numContacts,
										  real duration)
	{
		// Generate contact velocity and axis information.
		Contact* lastContact = contacts + numContacts;
		for (Contact* contact = contacts; contact < lastContact; contact++)
		{
			// Calculate the internal contact data (inertia, basis, etc).
			contact->CalculateInternals(duration);
		}
	}
	
	void ContactResolver::adjustVelocities(Contact *c,
										   unsigned numContacts,
										   real duration)
	{
		glm::vec3 velocityChange[2], rotationChange[2];
		glm::vec3 deltaVel;
	
		// iteratively handle impacts in order of severity.
		m_velocityIterationsUsed = 0;
		while (m_velocityIterationsUsed < m_velocityIterations)
		{
			// Find contact with maximum magnitude of probable velocity change.
			real max = m_velocityEpsilon;
			unsigned index = numContacts;
			for (unsigned i = 0; i < numContacts; i++)
			{
				if (c[i].m_desiredDeltaVelocity > max)
				{
					max = c[i].m_desiredDeltaVelocity;
					index = i;
				}
			}
			if (index == numContacts) break;
	
			// Match the awake state at the contact
			//c[index].matchAwakeState();
	
			// Do the resolution on the contact that came out top.
			c[index].ApplyVelocityChange(velocityChange, rotationChange);
	
			// With the change in velocity of the two bodies, the update of
			// contact velocities means that some of the relative closing
			// velocities need recomputing.
			for (unsigned i = 0; i < numContacts; i++)
			{
				// Check each body in the contact
				for (unsigned b = 0; b < 2; b++) if (c[i].m_body[b])
				{
					// Check for a match with each body in the newly
					// resolved contact
					for (unsigned d = 0; d < 2; d++)
					{
						if (c[i].m_body[b] == c[index].m_body[d])
						{
							deltaVel = velocityChange[d] +
								glm::cross(rotationChange[d], c[i].m_relativeContactPosition[b]);
	
							// The sign of the change is negative if we're dealing
							// with the second body in a contact.
							c[i].m_contactVelocity +=
								glm::transpose(c[i].m_contactToWorld) * deltaVel * 
								static_cast<real>((b ? -1 : 1));
								
							c[i].CalculateDesiredDeltaVelocity(duration);
						}
					}
				}
			}
			m_velocityIterationsUsed++;
		}
	}
	
	void ContactResolver::adjustPositions(Contact *c,
										  unsigned numContacts,
										  real duration)
	{
		unsigned i, index;
		glm::vec3 linearChange[2], angularChange[2];
		real max;
		glm::vec3 deltaPosition;
	
		// iteratively resolve interpenetrations in order of severity.
		m_positionIterationsUsed = 0;
		while (m_positionIterationsUsed < m_positionIterations)
		{
			// Find biggest penetration
			max = m_positionEpsilon;
			index = numContacts;
			for (i = 0; i<numContacts; i++)
			{
				if (c[i].m_penetration > max)
				{
					max = c[i].m_penetration;
					index = i;
				}
			}
			if (index == numContacts) break;
	
			// Match the awake state at the contact
			//c[index].matchAwakeState();
	
			// Resolve the penetration.
			c[index].ApplyPositionChange(
				linearChange,
				angularChange,
				max);
	
			// Again this action may have changed the penetration of other
			// bodies, so we update contacts.
			for (i = 0; i < numContacts; i++)
			{
				// Check each body in the contact
				for (unsigned b = 0; b < 2; b++) if (c[i].m_body[b])
				{
					// Check for a match with each body in the newly
					// resolved contact
					for (unsigned d = 0; d < 2; d++)
					{
						if (c[i].m_body[b] == c[index].m_body[d])
						{
							deltaPosition = linearChange[d] +
								glm::cross(angularChange[d], c[i].m_relativeContactPosition[b]);
	
							// The sign of the change is positive if we're
							// dealing with the second body in a contact
							// and negative otherwise (because we're
							// subtracting the resolution)..
							c[i].m_penetration +=
								glm::dot(deltaPosition, c[i].m_contactNormal) 
								* (b ? static_cast<real>(1.0f) : static_cast<real>(-1));
						}
					}
				}
			}
			m_positionIterationsUsed++;
		}
	}
	
	bool ContactResolver::isValid()
	{
		return (m_velocityIterations > 0) &&
			(m_positionIterations > 0) &&
			(m_positionEpsilon >= 0.0f) &&
			(m_positionEpsilon >= 0.0f);
	}
}