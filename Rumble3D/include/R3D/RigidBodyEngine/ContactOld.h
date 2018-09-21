#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC ContactOld
	{
		friend class ContactResolverOld;
	
	public:
		explicit ContactOld();
		~ContactOld();

		void setContactPoint(const glm::vec3& contactPoint);
		glm::vec3 getContactPoint() const;
		void setContactNormal(const glm::vec3& contactNormal);
		glm::vec3 getContactNormal() const;

		void setPenetration(real penetration);
		real getPenetration() const;

		void setBodyData(RigidBody* one, RigidBody* two,
						 real friction, real restitution);
		void calculateContactBasis();
		glm::vec3 calculateFrictionlessImpulse(glm::mat3* inverseInertiaTensor) const;

	protected:
		void calculateInternals(real duration);

		glm::vec3 calculateLocalVelocity(unsigned bodyIndex, real duration);
		void calculateDesiredDeltaVelocity(real duration);

		void swapBodies();

		void applyVelocityChange(glm::vec3 velocityChange[2],
								 glm::vec3 rotationChange[2]) const;
		void applyPositionChange(glm::vec3 linearChange[2],
								 glm::vec3 angularChange[2],
								 real penetration) const;

		/** 
		 * \brief The two rigid bodies, which are colliding. 
		 */
		RigidBody* m_body[2]{};

		real m_friction{};
		real m_restitution{};
		
		glm::vec3 m_contactPoint;
		glm::vec3 m_contactNormal;
		real m_penetration{};

		/** 
		 * Transformationsmatrix von Kontakt-Koordinaten in 
		 * Welt-Koordinaten. Spalten der Matrix sind Orthonormale 
		 * Vektoren.
		 */
		glm::mat3 m_contactToWorld;
		/**
		 * Closing Velocity. Mit calculateInternals gesetzt.
		 */
		glm::vec3 m_contactVelocity;
		/**
		 * Erforderliche Änderung der Geschwindigkeit für diesen 
		 * Kontakt. (Gegen Vibrationen)
		 */
		real m_desiredDeltaVelocity{};
		/**
		 * Welt - Koordinaten des Kontaktpunktes relativ zum 
		 * Schwerpunkt des Körpers.Mit calculateInternals gesetzt.
		 */
		glm::vec3 m_relativeContactPosition[2];

		static constexpr real s_velocityLimit = 0.25;
	};

}