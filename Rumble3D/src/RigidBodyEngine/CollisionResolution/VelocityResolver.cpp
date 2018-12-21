#include "R3D/RigidBodyEngine/CollisionResolution/VelocityResolver.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_cross_product.hpp>

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
		m_iterationsMax = iterations;
	}

	void VelocityResolver::setVelocityEpsilon(const real epsilon)
	{
		m_epsilon = glm::max(0.0f, epsilon);
	}

	glm::vec3 VelocityResolver::calculateFrictionlessImpulse(
		const Contact& contact,
		glm::mat3 inverseInertiaTensor[2]) const
	{
		glm::vec3 impulseContact;
		const auto first = contact.getFirst();
		const auto second = contact.getSecond();


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
			deltaVelWorld = glm::cross(deltaVelWorld, 
									   contact.getRelativeContactPosition(1));

			// Addition der linearen Komponente der Geschwindigkeitsänderung aus der Rotation:
			deltaVelocity += glm::dot(deltaVelWorld, 
									  contact.getContactNormal());

			// Addition der linearen Komponente der Geschwindigkeitsänderung:
			deltaVelocity += second->getInverseMass();
		}

		// Notwendiger Impuls:
		impulseContact.x = contact.getDesiredDeltaVelocity() / deltaVelocity;
		impulseContact.y = 0;
		impulseContact.z = 0;
		return impulseContact;
	}

	glm::vec3 VelocityResolver::calculateFrictionImpulse(
		const Contact& contact,
		glm::mat3 inverseInertiaTensor[2]) const
	{
		const auto first = contact.getFirst();
		const auto second = contact.getSecond();

		real inverseMass = first->getInverseMass();

		// The equivalent of a cross product in matrices is multiplication
		// by a skew symmetric matrix - we build the matrix for converting
		// between linear and angular quantities.
		glm::mat3 impulseToTorque = 
			glm::matrixCross3(contact.getRelativeContactPosition(0));

		// Build the matrix to convert contact impulse to change in velocity
		// in world coordinates.
		glm::mat3 deltaVelWorld = impulseToTorque;
		deltaVelWorld *= inverseInertiaTensor[0];
		deltaVelWorld *= impulseToTorque;
		deltaVelWorld *= -1;

		// Check if we need to add body two's data
		if(second->hasFiniteMass())
		{
			// Set the cross product matrix
			impulseToTorque =
				glm::matrixCross3(contact.getRelativeContactPosition(1));


			// Calculate the velocity change matrix
			glm::mat3 deltaVelWorld2 = impulseToTorque;
			deltaVelWorld2 *= inverseInertiaTensor[1];
			deltaVelWorld2 *= impulseToTorque;
			deltaVelWorld2 *= -1;

			// Add to the total delta velocity.
			deltaVelWorld += deltaVelWorld2;

			// Add to the inverse mass
			inverseMass += second->getInverseMass();
		}

		// Do a change of basis to convert into contact coordinates.
		glm::mat3 deltaVelocity = glm::transpose(contact.getContactToWorld());
		deltaVelocity *= deltaVelWorld;
		deltaVelocity *= contact.getContactToWorld();

		// Add in the linear velocity change
		deltaVelocity[0][0] += inverseMass;
		deltaVelocity[1][1] += inverseMass;
		deltaVelocity[2][2] += inverseMass;

		// Invert to get the impulse needed per unit velocity
		glm::mat3 impulseMatrix = glm::inverse(deltaVelocity);

		// Find the target velocities to kill
		
		glm::vec3 velKill(contact.getDesiredDeltaVelocity(),
						  -contact.getClosingVelocity().y,
						  -contact.getClosingVelocity().z);

		// Find the impulse to kill target velocities
		glm::vec3 impulseContact = impulseMatrix * velKill;

		// Check for exceeding friction
		real planarImpulse = sqrt(impulseContact.y * impulseContact.y +
								  impulseContact.z * impulseContact.z);

		const auto friction = contact.getFriction();
		if(planarImpulse > impulseContact.x * friction)
		{
			// We need to use dynamic friction
			impulseContact.y /= planarImpulse;
			impulseContact.z /= planarImpulse;

			impulseContact.x = deltaVelocity[0][0] +
				deltaVelocity[1][0] * friction * impulseContact.y +
				deltaVelocity[2][0] * friction * impulseContact.z;
			impulseContact.x = contact.getDesiredDeltaVelocity() / impulseContact.x;
			impulseContact.y *= friction * impulseContact.x;
			impulseContact.z *= friction * impulseContact.x;
		}
		return impulseContact;
	}

	void VelocityResolver::adjustVelocities(CollisionData& collisionData,
	                                        const real duration)
	{
		glm::vec3 velocityChange[2]{};
		glm::vec3 rotationChange[2]{};

		// iteratively handle impacts in order of severity.
		m_iterationsUsed = 0;
		while(m_iterationsUsed < m_iterationsMax)
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
			contact.matchAwakeState();
			applyVelocityChange(contact, velocityChange, rotationChange);

			// With the change in velocity of the two bodies, the update of
			// contact velocities means that some of the relative closing
			// velocities need recomputing.
			for(auto i = 0; i < collisionData.getContactsUsed(); ++i)
			{
				auto& it = data[i];

				// Check each body in the contact
				for(unsigned b = 0; b < 2; ++b)
				{
					auto* first = it.getBody(b);
					if(!first->hasFiniteMass()) continue;
					
					// Check for a match with each body in the newly
					// resolved contact
					for(unsigned d = 0; d < 2; ++d)
					{
						auto* second = contact.getBody(d);
						if(first != second) continue;
						
						glm::vec3 deltaVel = velocityChange[d] +
							glm::cross(rotationChange[d], it.getRelativeContactPosition(b));

						// The sign of the change is negative if we're dealing
						// with the second body in a contact.
						const auto direction = b == 1 ? real(-1) : real(1);
						deltaVel = glm::transpose(it.getContactToWorld()) * deltaVel * direction;
						it.setClosingVelocity(it.getClosingVelocity() + deltaVel);

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
		glm::mat3 inverseInertiaTensor[2]{};
		inverseInertiaTensor[0] = first->getInverseInertiaTensorWorld();
		if(second->hasFiniteMass())
		{
			inverseInertiaTensor[1] = second->getInverseInertiaTensorWorld();
		}

		// Berechnung des Impulses
		glm::vec3 impulseContact{};

		if(contact.getFriction() == real(0))
		{
			// Without friction
			impulseContact = calculateFrictionlessImpulse(contact,
														  inverseInertiaTensor);
		}
		else
		{
			//impulseContact = calculateFrictionlessImpulse(contact,
			//											  inverseInertiaTensor);
			// With friction
			impulseContact = calculateFrictionImpulse(contact, 
													  inverseInertiaTensor);
		}

		// Konvertiere Impuls in Welt-Koordinaten
		const auto impulse = contact.getContactToWorld() * impulseContact;

		// Aufspaltung in lineare und rotational Komponente:
		glm::vec3 impulsiveTorque = glm::cross(contact.getRelativeContactPosition(0), impulse);
		rotationChange[0] = inverseInertiaTensor[0] * impulsiveTorque;
		velocityChange[0] = first->getInverseMass() * impulse;

		// Änderungen auf Körper anwenden:
		first->addVelocity(velocityChange[0]);
		first->addRotation(rotationChange[0]);

		if(second->hasFiniteMass())
		{
			// Für zweiten Körper; Drehmoment negativ; 
			// erreicht durch Operandentausch imKreuzprodukt:
			impulsiveTorque = glm::cross(impulse, contact.getRelativeContactPosition(1));
			rotationChange[1] = inverseInertiaTensor[1] * impulsiveTorque;
			velocityChange[1] = -second->getInverseMass() * impulse;

			// Anwendung:
			second->addVelocity(velocityChange[1]);
			second->addRotation(rotationChange[1]);
		}
	}

	VelocityResolver::VelocityResolver()
		: m_epsilon(real(0.01)),
		m_iterationsUsed(0),
		m_iterationsMax(1)
	{
	}
}

#undef GLM_ENABLE_EXPERIMENTAL