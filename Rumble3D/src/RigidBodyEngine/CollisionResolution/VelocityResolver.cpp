#include "R3D/RigidBodyEngine/CollisionResolution/VelocityResolver.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include <algorithm>

namespace r3
{
	VelocityResolver::~VelocityResolver()
	= default;

	void VelocityResolver::resolve(CollisionData& collisionData,
	                               const real timeDelta)
	{
		adjustVelocities(collisionData, timeDelta);
	}

	void VelocityResolver::setMaxIterations(const unsigned iterations)
	{
		m_iterations = iterations;
	}

	void VelocityResolver::setVelocityEpsilon(const real epsilon)
	{
		m_epsilon = glm::max(0.0f, epsilon);
	}

	glm::vec3 VelocityResolver::calculateFrictionlessImpulse(const Contact& contact,
															 glm::mat3 inverseInertiaTensor[2]) const
	{
		glm::vec3 impulseContact;
		auto* first = contact.getFirst();
		auto* second = contact.getSecond();


		// Erstelle Vektor für die Geschwindigkeitsänderung in World-Koordinaten
		// für eine Impulseinheit in Richtung Kontaktnormale:
		glm::vec3 deltaVelWorld = glm::cross(contact.getRelativeContactPosition(0), 
											 contact.getContactNormal());
		deltaVelWorld = inverseInertiaTensor[0] * deltaVelWorld;
		deltaVelWorld = glm::cross(deltaVelWorld, contact.getRelativeContactPosition(0));

		// Umwandlung in Kontaktkoordinaten
		auto deltaVelocity = glm::dot(deltaVelWorld, contact.getContactNormal());

		// Addition der linearen Komponente der Geschwindigkeitsänderung:
		deltaVelocity += first->getInverseMass();

		if(second->hasFiniteMass())
		{
			// Gleiche Transformation:
			glm::vec3 deltaVelWorld = glm::cross(contact.getRelativeContactPosition(1),
												 contact.getContactNormal());
			deltaVelWorld = inverseInertiaTensor[1] * deltaVelWorld;
			deltaVelWorld = glm::cross(deltaVelWorld, contact.getRelativeContactPosition(1));

			// Addition der linearen Komponente der Geschwindigkeitsänderung aus der Rotation:
			deltaVelocity += glm::dot(deltaVelWorld, contact.getContactNormal());

			// Addition der linearen Komponente der Geschwindigkeitsänderung:
			deltaVelocity += second->getInverseMass();
		}

		// Notwendiger Impuls:
		impulseContact.x = contact.getDesiredDeltaVelocity() / deltaVelocity;
		impulseContact.y = 0;
		impulseContact.z = 0;
		return impulseContact;
	}

	void VelocityResolver::adjustVelocities(CollisionData& collisionData,
	                                        const real duration)
	{
		glm::vec3 velocityChange[2]{};
		glm::vec3 rotationChange[2]{};

		// iteratively handle impacts in order of severity.
		m_iterationsUsed = 0;
		while(m_iterationsUsed < m_iterations)
		{
			// Find contact with maximum magnitude of probable velocity change.			
			auto& data = collisionData.getData();
			auto maxIndex = -1;
			auto maxValue = m_epsilon;
			for(int i = 0; i < collisionData.getContactsUsed(); ++i)
			{
				auto value = data[i].getDesiredDeltaVelocity();
				if(value > maxValue)
				{
					maxValue = value;
					maxIndex = i;
				}
			}			

			// Check if there was at least one contact with a value
			// larger than epsilon.
			if(maxIndex == -1)
			{
				return;
			}

			// Match the awake state at the contact
			//c[index].matchAwakeState();

			auto& contact = data[maxIndex];
			applyVelocityChange(contact, velocityChange, rotationChange);

			// With the change in velocity of the two bodies, the update of
			// contact velocities means that some of the relative closing
			// velocities need recomputing.
			for(auto i = 0; i < collisionData.getContactsUsed(); ++i)
			{
				auto& it = data[i];

				// Check each body in the contact
				for(unsigned b = 0; b < 2; b++)
				{
					auto* first = b == 0 ? it.getFirst() : it.getSecond();
					if(!first) continue;
					
					// Check for a match with each body in the newly
					// resolved contact
					for(unsigned d = 0; d < 2; d++)
					{
						auto* second = d == 0 ? contact.getFirst() : contact.getSecond();
						if(first != second) continue;
						
						glm::vec3 deltaVel = velocityChange[d] +
							glm::cross(rotationChange[d], it.getRelativeContactPosition(b));

						// The sign of the change is negative if we're dealing
						// with the second body in a contact.
						const auto direction = static_cast<real>(b ? -1 : 1);
						deltaVel = glm::transpose(it.getContactToWorld()) * deltaVel * direction;
						it.setContactVelocity(it.getContactVelocity() + deltaVel);

						it.calculateDesiredDeltaVelocity(duration);
					}
				}
			}
			m_iterationsUsed++;
		}
	}

	void VelocityResolver::applyVelocityChange(const Contact& contact,
											   glm::vec3 velocityChange[2],
											   glm::vec3 rotationChange[2]) const
	{
		auto* first = contact.getFirst();
		auto* second = contact.getSecond();

		// Zwischenspeichern der inversen Trägheitstensoren in Weltkoordinaten
		glm::mat3 inverseInertiaTensor[2];
		first->getInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
		if(second->hasFiniteMass())
		{
			second->getInverseInertiaTensorWorld(&inverseInertiaTensor[1]);
		}

		// Berechnung des Impulses
		glm::vec3 impulseContact;

		if(contact.getFriction() == static_cast<real>(0.0f))
		{
			// Ohne Reibung
			impulseContact = calculateFrictionlessImpulse(contact,
														  inverseInertiaTensor);
		}
		else
		{
			impulseContact = calculateFrictionlessImpulse(contact,
														  inverseInertiaTensor);
			// Mit Reibung: komplexere Version; nicht implementiert !!!
			// impulseContact = calculateFrictionImpulse(inverseInertiaTensor);
		}

		// Konvertiere Impuls in Welt-Koordinaten
		const auto impulse = contact.getContactToWorld() * impulseContact;

		// Aufspaltung in lineare und rotational Komponente:
		glm::vec3 impulsiveTorque = glm::cross(contact.getRelativeContactPosition(0), impulse);
		rotationChange[0] = inverseInertiaTensor[0] * impulsiveTorque;
		velocityChange[0] = glm::vec3(static_cast<real>(0.0f));
		velocityChange[0] += first->getInverseMass() * impulse;

		// Änderungen auf Körper anwenden:
		first->addVelocity(velocityChange[0]);
		first->addRotation(rotationChange[0]);

		if(second->hasFiniteMass())
		{
			// Für zweiten Körper; Drehmoment negativ; 
			// erreicht durch Operandentausch imKreuzprodukt:
			impulsiveTorque = glm::cross(impulse, contact.getRelativeContactPosition(1));
			rotationChange[1] = inverseInertiaTensor[1] * impulsiveTorque;
			velocityChange[1] = glm::vec3(static_cast<real>(0.0f));
			velocityChange[1] += -second->getInverseMass() * impulse;

			// Anwendung:
			second->addVelocity(velocityChange[1]);
			second->addRotation(rotationChange[1]);
		}
	}

	VelocityResolver::VelocityResolver()
		: m_epsilon(0.01),
		m_iterationsUsed(0),
		m_iterations(1)
	{
	}
}
