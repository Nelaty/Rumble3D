#include "R3D/RigidBodyEngine/CollisionResolution/InterpenetrationResolver.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include <algorithm>


namespace r3
{
	InterpenetrationResolver::~InterpenetrationResolver()
	= default;

	void InterpenetrationResolver::resolve(CollisionData& collisionData,
	                                       const real timeDelta)
	{
		adjustPositions(collisionData, timeDelta);
	}

	void InterpenetrationResolver::setMaxIterations(const unsigned iterations)
	{
		m_iterations = iterations;
	}

	void InterpenetrationResolver::setPositionEpsilon(const real epsilon)
	{
		m_epsilon = epsilon;
	}

	void InterpenetrationResolver::adjustPositions(CollisionData& collisionData,
	                                               const real timeDelta)
	{
		// iteratively resolve interpenetrations in order of severity.
		m_iterationsUsed = 0;
		while (m_iterationsUsed < m_iterations)
		{
			glm::vec3 linearChange[2];
			glm::vec3 angularChange[2];

			// Find biggest penetration		
			auto& data = collisionData.getData();
			auto maxIndex = -1;
			auto maxValue = m_epsilon;
			for (int i = 0; i < collisionData.getContactsUsed(); ++i)
			{
				auto value = data[i].getPenetration();
				if (value > maxValue)
				{
					maxValue = value;
					maxIndex = i;
				}
			}

			// Check if there was at least one contact with a value
			// larger than epsilon.
			if (maxIndex == -1)
			{
				return;
			}

			// Match the awake state at the contact
			//c[index].matchAwakeState();

			auto& contact = data[maxIndex];
			applyPositionChange(linearChange, angularChange, contact);

			// Again this action may have changed the penetration of other
			// bodies, so we update contacts.
			for (auto i = 0; i < collisionData.getContactsUsed(); ++i)
			{
				auto& it = data[i];
				for (auto b = 0; b < 2; b++)
				{
					auto* first = b == 0 ? it.getFirst() : it.getSecond();
					if (!first) continue;

					for (auto d = 0; d < 2; ++d)
					{
						auto* second = d == 0 ? contact.getFirst() : contact.getSecond();
						if (first != second) continue;

						auto deltaPosition = linearChange[d] +
							glm::cross(angularChange[d], it.getRelativeContactPosition(b));

						// The sign of the change is positive if we're
						// dealing with the second body in a contact
						// and negative otherwise (because we're
						// subtracting the resolution)..
						auto direction = b ? static_cast<real>(1.0f) : static_cast<real>(-1);
						auto deltaPenetration = glm::dot(deltaPosition, it.getContactNormal()) * direction;
						it.setPenetration(it.getPenetration() + deltaPenetration);
					}
				}
			}
			m_iterationsUsed++;
		}
	}

	void InterpenetrationResolver::applyPositionChange(glm::vec3 linearChange[2],
	                                                   glm::vec3 angularChange[2],
	                                                   const Contact& contact) const
	{
		const auto penetration = contact.getPenetration();

		const auto angularLimit = static_cast<real>(0.2f);
		real angularMove[2] = {0.0f, 0.0f};
		real linearMove[2] = {0.0f, 0.0f};

		real totalInertia = 0.0f;
		real linearInertia[2] = {0.0f, 0.0f};
		real angularInertia[2] = {0.0f, 0.0f};

		// We need to work out the inertia of each object in the direction
		// of the contact normal, due to angular inertia only.
		for (unsigned i = 0; i < 2; i++)
		{
			auto* body = contact.getBody(i);
			if (body->hasFiniteMass())
			{
				glm::mat3 inverseInertiaTensor;
				body->getInverseInertiaTensorWorld(&inverseInertiaTensor);

				// Use the same procedure as for calculating frictionless
				// velocity change to work out the angular inertia.
				glm::vec3 angularInertiaWorld = glm::cross(contact.getRelativeContactPosition(i),
				                                           contact.getContactNormal());
				angularInertiaWorld = inverseInertiaTensor * angularInertiaWorld;
				angularInertiaWorld = glm::cross(angularInertiaWorld, contact.getRelativeContactPosition(i));
				angularInertia[i] = glm::dot(angularInertiaWorld, contact.getContactNormal());

				// The linear component is simply the inverse mass
				linearInertia[i] = body->getInverseMass();

				// Keep track of the total inertia from all components
				totalInertia += linearInertia[i] + angularInertia[i];

				// We break the loop here so that the totalInertia value is
				// completely calculated (by both iterations) before
				// continuing.
			}
		}

		// Loop through again calculating and applying the changes
		for (unsigned i = 0; i < 2; i++)
		{
			auto* body = contact.getBody(i);
			if (body)
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
				glm::vec3 projection = contact.getRelativeContactPosition(i);
				projection += glm::dot(-contact.getRelativeContactPosition(i), contact.getContactNormal()) * contact.
					getContactNormal();

				// Use the small angle approximation for the sine of the angle (i.e.
				// the magnitude would be sine(angularLimit) * projection.magnitude
				// but we approximate sine(angularLimit) to angularLimit).
				const auto maxMagnitude = angularLimit * glm::length(projection);

				if (angularMove[i] < -maxMagnitude)
				{
					const auto totalMove = angularMove[i] + linearMove[i];
					angularMove[i] = -maxMagnitude;
					linearMove[i] = totalMove - angularMove[i];
				}
				else if (angularMove[i] > maxMagnitude)
				{
					const auto totalMove = angularMove[i] + linearMove[i];
					angularMove[i] = maxMagnitude;
					linearMove[i] = totalMove - angularMove[i];
				}

				// We have the linear amount of movement required by turning
				// the rigid body (in angularMove[i]). We now need to
				// calculate the desired rotation to achieve that.
				if (angularMove[i] == 0)
				{
					// Easy case - no angular movement means no rotation.
					angularChange[i] = glm::vec3(static_cast<real>(0.0f));
				}
				else
				{
					// Work out the direction we'd like to rotate in.
					glm::vec3 targetAngularDirection = glm::cross(contact.getRelativeContactPosition(i),
					                                              contact.getContactNormal());

					glm::mat3 inverseInertiaTensor;
					body->getInverseInertiaTensorWorld(&inverseInertiaTensor);

					// Work out the direction we'd need to rotate to achieve that
					angularChange[i] = (angularMove[i] / angularInertia[i]) *
						inverseInertiaTensor * targetAngularDirection;
				}

				// Velocity change is easier - it is just the linear movement
				// along the contact normal.
				linearChange[i] = contact.getContactNormal() * linearMove[i];

				// Now we can start to apply the values we've calculated.
				// Apply the linear movement
				auto pos = body->getCenterOfMass();
				pos += linearMove[i] * contact.getContactNormal();
				body->setCenterOfMass(pos);

				// And the change in orientation
				auto q = body->getOrientation();
				//q.addScaledVector(angularChange[i], static_cast<real>(1.0)); // ACHTUNG in RegisterForce... *0,5!!!
				q += (glm::quat(static_cast<real>(0.0f), angularChange[i] * static_cast<real>(1.0)) * q * static_cast<
					real>(0.5f));

				body->setOrientation(q);

				// We need to calculate the derived data for any body that is
				// asleep, so that the changes are reflected in the object's
				// data. Otherwise the resolution will not change the position
				// of the object, and the next collision detection round will
				// have the same penetration.
				//if (!m_body[i]->getAwake()) m_body[i]->calculateDerivedData();
			}
		}
	}

	InterpenetrationResolver::InterpenetrationResolver()
		: m_epsilon(static_cast<real>(0.01f)),
		  m_iterationsUsed(0),
		  m_iterations(1)
	{
	}
}
