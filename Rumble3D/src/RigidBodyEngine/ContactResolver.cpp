#include "R3D/RigidBodyEngine/ContactResolver.h"
#include "R3D/RigidBodyEngine/Contact.h"

#include <glm/glm.hpp>

namespace rum
{
	
	ContactResolver::ContactResolver(const unsigned iterations,
	                                 const real velocityEpsilon,
	                                 const real positionEpsilon)
	{
		setIterations(iterations, iterations);
		setEpsilon(velocityEpsilon, positionEpsilon);
	}

	ContactResolver::ContactResolver(const unsigned velocityIterations,
	                                 const unsigned positionIterations,
	                                 const real velocityEpsilon,
	                                 const real positionEpsilon)
		: m_positionIterations{positionIterations}
	{
		setIterations(velocityIterations);
		setEpsilon(velocityEpsilon, positionEpsilon);
	}
	
	void ContactResolver::setIterations(const unsigned iterations)
	{
		setIterations(iterations, iterations);
	}
	
	void ContactResolver::setIterations(const unsigned velocityIterations,
	                                    const unsigned positionIterations)
	{
		m_velocityIterations = velocityIterations;
		m_positionIterations = positionIterations;
	}
	
	void ContactResolver::setEpsilon(const real velocityEpsilon,
	                                 const real positionEpsilon)
	{
		m_velocityEpsilon = velocityEpsilon;
		m_positionEpsilon = positionEpsilon;
	}
	
	void ContactResolver::resolveContacts(Contact *contacts,
	                                      const unsigned numContacts,
	                                      const real timeDelta)
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
		prepareContacts(contacts, numContacts, timeDelta);
	
		// Resolve the interpenetration problems with the contacts.
		adjustPositions(contacts, numContacts, timeDelta);
	
		// Resolve the velocity problems with the contacts.
		adjustVelocities(contacts, numContacts, timeDelta);
	}
	
	void ContactResolver::prepareContacts(Contact* contacts,
	                                      const unsigned numContacts,
	                                      const real timeDelta)
	{
		// Generate contact velocity and axis information.
		Contact* lastContact = contacts + numContacts;
		for (Contact* contact = contacts; contact < lastContact; contact++)
		{
			// Calculate the internal contact data (inertia, basis, etc).
			contact->calculateInternals(timeDelta);
		}
	}
	
	void ContactResolver::adjustVelocities(Contact *c,
	                                       const unsigned numContacts,
	                                       const real timeDelta)
	{
		glm::vec3 velocityChange[2], rotationChange[2];

		// iteratively handle impacts in order of severity.
		m_velocityIterationsUsed = 0;
		while (m_velocityIterationsUsed < m_velocityIterations)
		{
			// Find contact with maximum magnitude of probable velocity change.
			auto max = m_velocityEpsilon;
			auto index = numContacts;
			for (unsigned i = 0; i < numContacts; i++)
			{
				if (c[i].m_desiredDeltaVelocity > max)
				{
					max = c[i].m_desiredDeltaVelocity;
					index = i;
				}
			}
			if(index == numContacts) break;
	
			// Match the awake state at the contact
			//c[index].matchAwakeState();
	
			// Do the resolution on the contact that came out top.
			c[index].applyVelocityChange(velocityChange, rotationChange);
	
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
							glm::vec3 deltaVel = velocityChange[d] +
								glm::cross(rotationChange[d], c[i].m_relativeContactPosition[b]);
	
							// The sign of the change is negative if we're dealing
							// with the second body in a contact.
							c[i].m_contactVelocity +=
								glm::transpose(c[i].m_contactToWorld) * deltaVel * 
								static_cast<real>((b ? -1 : 1));
								
							c[i].calculateDesiredDeltaVelocity(timeDelta);
						}
					}
				}
			}
			m_velocityIterationsUsed++;
		}
	}
	
	void ContactResolver::adjustPositions(Contact *c,
	                                      const unsigned numContacts,
										  real timeDelta)
	{
		unsigned i;
		glm::vec3 linearChange[2], angularChange[2];

		// iteratively resolve interpenetrations in order of severity.
		m_positionIterationsUsed = 0;
		while (m_positionIterationsUsed < m_positionIterations)
		{
			// Find biggest penetration
			auto max = m_positionEpsilon;
			auto index = numContacts;
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
			c[index].applyPositionChange(
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
							auto deltaPosition = linearChange[d] +
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
	
	bool ContactResolver::isValid() const
	{
		return (m_velocityIterations > 0) &&
			(m_positionIterations > 0) &&
			(m_positionEpsilon >= 0.0f) &&
			(m_positionEpsilon >= 0.0f);
	}
}