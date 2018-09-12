#include "R3D/RigidBodyEngine/ContactOld.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include <utility>

namespace r3
{
	ContactOld::ContactOld()
	= default;

	ContactOld::~ContactOld()
	= default;

	void ContactOld::setContactPoint(const glm::vec3& contactPoint)
	{
		m_contactPoint = contactPoint;
	}
	
	glm::vec3 ContactOld::getContactPoint() const
	{
		return m_contactPoint;
	}
	
	void ContactOld::setContactNormal(const glm::vec3& contactNormal)
	{
		m_contactNormal = contactNormal;
	}
	
	glm::vec3 ContactOld::getContactNormal() const
	{
		return m_contactNormal;
	}
	
	void ContactOld::setPenetration(const real penetration)
	{
		m_penetration = penetration;
	}
	
	real ContactOld::getPenetration() const
	{
		return m_penetration;
	}
	
	void ContactOld::setBodyData(RigidBody* one, 
							  RigidBody* two,
	                          const real friction,
	                          const real restitution) 
	{
		m_body[0] = one;
		m_body[1] = two;
		m_friction = friction;
		m_restitution = restitution;
	}
	
	void ContactOld::calculateContactBasis()
	{
		glm::vec3 contactTangent[2];
		const auto contactNormalX = m_contactNormal.x;
		const auto contactNormalY = m_contactNormal.y;
		const auto contactNormalZ = m_contactNormal.z;
	
		// Check whether the Z-axis is nearer to the X or Y axis
		if (abs(contactNormalX) > abs(contactNormalY))
		{
			// Scaling factor to ensure the results are normalized
			const auto s = static_cast<real>(1.0f) / sqrt(contactNormalZ*contactNormalZ +
				contactNormalX*contactNormalX);
	
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
				contactNormalY*contactNormalY);
	
			// The new X-axis is at right angles to the world X-axis
			contactTangent[0].x = 0;
			contactTangent[0].y = s * -contactNormalZ;
			contactTangent[0].z = s * contactNormalY;
	
			// The new Y-axis is at right angles to the new X- and Z- axes
			contactTangent[1].x = contactNormalY*contactTangent[0].z -
				contactNormalZ*contactTangent[0].y;
			contactTangent[1].y = -contactNormalX*contactTangent[0].z;
			contactTangent[1].z = contactNormalX*contactTangent[0].y;
		}
	
		// Make a matrix from the three vectors.
		m_contactToWorld[0] = m_contactNormal;
		m_contactToWorld[1] = contactTangent[0];
		m_contactToWorld[2] = contactTangent[1];
	}
	
	glm::vec3 ContactOld::calculateFrictionlessImpulse(glm::mat3* inverseInertiaTensor)
	{
		glm::vec3 impulseContact;
		
		// Erstelle Vektor für die Geschwindigkeitsänderung in World-Koordinaten
		// für eine Impulseinheit in Richtung Kontaktnormale:
		glm::vec3 deltaVelWorld = glm::cross(m_relativeContactPosition[0], m_contactNormal);
		deltaVelWorld = inverseInertiaTensor[0] * deltaVelWorld;
		deltaVelWorld = glm::cross(deltaVelWorld, m_relativeContactPosition[0]);
	
		// Umwandlung in Kontaktkoordinaten
		auto deltaVelocity = glm::dot(deltaVelWorld, m_contactNormal);
	
		// Addition der linearen Komponente der Geschwindigkeitsänderung:
		deltaVelocity += m_body[0]->getInverseMass();
	
		if (m_body[1])
		{
			// Gleiche Transformation:
			glm::vec3 deltaVelWorld = glm::cross(m_relativeContactPosition[1], m_contactNormal);
			deltaVelWorld = inverseInertiaTensor[1] * deltaVelWorld;
			deltaVelWorld = glm::cross(deltaVelWorld, m_relativeContactPosition[1]);
	
			// Addition der linearen Komponente der Geschwindigkeitsänderung aus der Rotation:
			deltaVelocity += glm::dot(deltaVelWorld, m_contactNormal);
	
			// Addition der linearen Komponente der Geschwindigkeitsänderung:
			deltaVelocity += m_body[1]->getInverseMass();
		}
	
		// Notwendiger Impuls:
		impulseContact.x = m_desiredDeltaVelocity / deltaVelocity;
		impulseContact.y = 0;
		impulseContact.z = 0;
		return impulseContact;
	}
	
	void ContactOld::calculateInternals(const real duration)
	{
		// Check if the first object is NULL, and swap if it is.
		if(!m_body[0])
		{
			swapBodies();
		}

		// Calculate an set of axis at the contact point.
		calculateContactBasis();
	
		// Store the relative position of the contact relative to each body
		m_relativeContactPosition[0] = m_contactPoint - m_body[0]->getCenterOfMass();
		if (m_body[1]) {
			m_relativeContactPosition[1] = m_contactPoint - m_body[1]->getCenterOfMass();
		}
	
		// Find the relative velocity of the bodies at the contact point.
		m_contactVelocity = calculateLocalVelocity(0, duration);
		if (m_body[1]) {
			m_contactVelocity -= calculateLocalVelocity(1, duration);
		}
	
		// Calculate the desired change in velocity for resolution
		calculateDesiredDeltaVelocity(duration);
	}
	
	glm::vec3 ContactOld::calculateLocalVelocity(const unsigned bodyIndex, const real duration)
	{
		const auto thisBody = m_body[bodyIndex];
	
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
	
	void ContactOld::calculateDesiredDeltaVelocity(const real duration)
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
		if (abs(m_contactVelocity.x) < s_velocityLimit)
		{
			thisRestitution = static_cast<real>(0.0f);
		}
	
		m_desiredDeltaVelocity =
			-m_contactVelocity.x
			- thisRestitution * m_contactVelocity.x; //- velocityFromAcc);
	
	
		// -thisRestitution * m_contactVelocity.x - velocityFromAcc);
	}
	
	void ContactOld::swapBodies()
	{
		m_contactNormal *= -1;
		std::swap(m_body[0], m_body[1]);
	}
	
	void ContactOld::applyVelocityChange(glm::vec3 velocityChange[2],
									  glm::vec3 rotationChange[2])
	{
		// Zwischenspeichern der inversen Trägheitstensoren in Weltkoordinaten
		glm::mat3 inverseInertiaTensor[2];
		m_body[0]->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
		if(m_body[1])
		{
			m_body[1]->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);
		}

		// Berechnung des Impulses
		glm::vec3 impulseContact;
	
		if (m_friction == static_cast<real>(0.0f))
		{
			// Ohne Reibung
			impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
		}
		else
		{
			// Mit Reibung: komplexere Version; nicht implementiert !!!
			// impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
		}
	
		// Konvertiere Impuls in Welt-Koordinaten
		const auto impulse = m_contactToWorld * impulseContact;
	
		// Aufspaltung in lineare und rotational Komponente:
		glm::vec3 impulsiveTorque = glm::cross(m_relativeContactPosition[0], impulse);
		rotationChange[0] = inverseInertiaTensor[0] * impulsiveTorque;
		velocityChange[0] = glm::vec3(static_cast<real>(0.0f));
		velocityChange[0] += m_body[0]->getInverseMass() * impulse;

		// Änderungen auf Körper anwenden:
		m_body[0]->addVelocity(velocityChange[0]);
		m_body[0]->addRotation(rotationChange[0]);
	
		if (m_body[1])
		{
			// Für zweiten Körper; Drehmoment negativ; 
			// erreicht durch Operandentausch imKreuzprodukt:
			impulsiveTorque = glm::cross(impulse, m_relativeContactPosition[1]); 
			rotationChange[1] = inverseInertiaTensor[1] * impulsiveTorque;
			velocityChange[1] = glm::vec3(static_cast<real>(0.0f));
			velocityChange[1] += -m_body[1]->getInverseMass() * impulse;
	
			// Anwendung:
			m_body[1]->addVelocity(velocityChange[1]);
			m_body[1]->addRotation(rotationChange[1]);
		}
	}
	
	void ContactOld::applyPositionChange(glm::vec3 linearChange[2],
									  glm::vec3 angularChange[2],
	                                  const real penetration)
	{
		const auto angularLimit = static_cast<real>(0.2f);
		real angularMove[2];
		real linearMove[2];
	
		real totalInertia = 0;
		real linearInertia[2];
		real angularInertia[2];
	
		// We need to work out the inertia of each object in the direction
		// of the contact normal, due to angular inertia only.
		for(unsigned i = 0; i < 2; i++)
		{
			if(m_body[i])
			{
				glm::mat3 inverseInertiaTensor;
				m_body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

				// Use the same procedure as for calculating frictionless
				// velocity change to work out the angular inertia.
				glm::vec3 angularInertiaWorld = glm::cross(m_relativeContactPosition[i],
														   m_contactNormal);
				angularInertiaWorld = inverseInertiaTensor * angularInertiaWorld;
				angularInertiaWorld = glm::cross(angularInertiaWorld, m_relativeContactPosition[i]);
				angularInertia[i] = glm::dot(angularInertiaWorld, m_contactNormal);

				// The linear component is simply the inverse mass
				linearInertia[i] = m_body[i]->getInverseMass();

				// Keep track of the total inertia from all components
				totalInertia += linearInertia[i] + angularInertia[i];

				// We break the loop here so that the totalInertia value is
				// completely calculated (by both iterations) before
				// continuing.
			}
		}
	
		// Loop through again calculating and applying the changes
		for(unsigned i = 0; i < 2; i++)
		{
			if(m_body[i])
			{
				// The linear and angular movements required are in proportion to
				// the two inverse inertias.
				const auto sign = (i == 0) ? static_cast<real>(1.0f) : static_cast<real>(-1);
				angularMove[i] =
					sign * penetration * (angularInertia[i] / totalInertia);
				linearMove[i] =
					sign * penetration * (linearInertia[i] / totalInertia);

				// To avoid angular projections that are too great (when mass is large
				// but inertia tensor is small) limit the angular move.
				glm::vec3 projection = m_relativeContactPosition[i];
				projection += glm::dot(-m_relativeContactPosition[i], m_contactNormal) * m_contactNormal;

				// Use the small angle approximation for the sine of the angle (i.e.
				// the magnitude would be sine(angularLimit) * projection.magnitude
				// but we approximate sine(angularLimit) to angularLimit).
				const auto maxMagnitude = angularLimit * glm::length(projection);

				if(angularMove[i] < -maxMagnitude)
				{
					const auto totalMove = angularMove[i] + linearMove[i];
					angularMove[i] = -maxMagnitude;
					linearMove[i] = totalMove - angularMove[i];
				}
				else if(angularMove[i] > maxMagnitude)
				{
					const auto totalMove = angularMove[i] + linearMove[i];
					angularMove[i] = maxMagnitude;
					linearMove[i] = totalMove - angularMove[i];
				}

				// We have the linear amount of movement required by turning
				// the rigid body (in angularMove[i]). We now need to
				// calculate the desired rotation to achieve that.
				if(angularMove[i] == 0)
				{
					// Easy case - no angular movement means no rotation.
					angularChange[i] = glm::vec3(static_cast<real>(0.0f));
				}
				else
				{
					// Work out the direction we'd like to rotate in.
					glm::vec3 targetAngularDirection = glm::cross(m_relativeContactPosition[i], m_contactNormal);

					glm::mat3 inverseInertiaTensor;
					m_body[i]->getInverseInertiaTensorWorld(&inverseInertiaTensor);

					// Work out the direction we'd need to rotate to achieve that
					angularChange[i] = (angularMove[i] / angularInertia[i]) *
						inverseInertiaTensor * targetAngularDirection;
				}

				// Velocity change is easier - it is just the linear movement
				// along the contact normal.
				linearChange[i] = m_contactNormal * linearMove[i];

				// Now we can start to apply the values we've calculated.
				// Apply the linear movement
				auto pos = m_body[i]->getCenterOfMass();
				pos += linearMove[i] * m_contactNormal;
				m_body[i]->setCenterOfMass(pos);

				// And the change in orientation
				auto q = m_body[i]->getOrientation();
				//q.addScaledVector(angularChange[i], static_cast<real>(1.0)); // ACHTUNG in RegisterForce... *0,5!!!
				q += (glm::quat(static_cast<real>(0.0f), angularChange[i] * static_cast<real>(1.0)) * q * static_cast<real>(0.5f));

				m_body[i]->setOrientation(q);

				// We need to calculate the derived data for any body that is
				// asleep, so that the changes are reflected in the object's
				// data. Otherwise the resolution will not change the position
				// of the object, and the next collision detection round will
				// have the same penetration.
				//if (!m_body[i]->getAwake()) m_body[i]->calculateDerivedData();
			}
		}
	}
}