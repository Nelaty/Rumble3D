#pragma once
#include "R3D/Common/Precision.h"
#include "RigidBody.h"

namespace rum
{
	class Contact
	{
		friend class ContactResolver;
	
	public:
		void SetContactPoint(const glm::vec3& contactPoint);
		glm::vec3 GetContactPoint();
		void SetContactNormal(const glm::vec3& contactNormal);
		glm::vec3 GetContactMormal();

		void SetPenetration(const real penetration);
		real GetPenetration();

		void SetBodyData(RigidBody* one, RigidBody* two,
						 real friction, real restitution);
		void CalculateContactBasis();
		glm::vec3 CalculateFrictionlessImpulse(glm::mat3* inverseInertiaTensor);

	protected:
		void CalculateInternals(real duration);

		glm::vec3 CalculateLocalVelocity(unsigned bodyIndex, real duration);
		void CalculateDesiredDeltaVelocity(real duration);

		void SwapBodies();

		void ApplyVelocityChange(glm::vec3 velocityChange[2],
								 glm::vec3 rotationChange[2]);
		void ApplyPositionChange(glm::vec3 linearChange[2],
								 glm::vec3 angularChange[2],
								 real penetration);

		RigidBody* m_body[2];
		real m_friction;
		real m_restitution;
		glm::vec3 m_contactPoint;
		glm::vec3 m_contactNormal;
		real m_penetration;
		// Transformationsmatrix von Kontakt-Koordinaten 
		// in Welt-Koordinaten. Spalten der Matrix sind
		// Orthonormale Vektoren.
		glm::mat3 m_contactToWorld;
		// Closing Velocity. Mit calculateInternals gesetzt.
		glm::vec3 m_contactVelocity;
		// Erforderliche Änderung der Geschwindigkeit für 
		// diesen Kontakt. (Gegen Vibrationen)
		real m_desiredDeltaVelocity;
		// Welt - Koordinaten des Kontaktpunktes relativ zum 
		// Schwerpunkt des Körpers.Mit calculateInternals gesetzt.
		glm::vec3 m_relativeContactPosition[2];
	};

}