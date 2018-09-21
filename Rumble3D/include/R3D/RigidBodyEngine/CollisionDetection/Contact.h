#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "CollisionPair.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC Contact
	{
	public:
		explicit Contact();
		~Contact();

		/** Get the first colliding rigid body. */
		RigidBody* getFirst() const;
		/** Get the second colliding rigid body. */
		RigidBody* getSecond() const;

		/** 
		 * Get a rigid body by index.
		 * \return The first body if index == 0, the second one if index == 1. 
		 */
		RigidBody* getBody(int index) const;

		/** Set the point, where the collision took place. */
		void setContactPoint(const glm::vec3& contactPoint);
		/** Get the point, where the collision took place. */
		const glm::vec3& getContactPoint() const;

		/** Set the direction of the collision at the contact point. */
		void setContactNormal(const glm::vec3& contactNormal);
		/** Get the direction of the collision at the contact point. */
		glm::vec3 getContactNormal() const;

		/** Set the amount of interpenetration along the contact normal. */
		void setPenetration(real penetration);
		/** Get the amount of interpenetration. */
		real getPenetration() const;

		/** Set involved rigid bodies, friction and restitution coefficients. */
		void setBodyData(RigidBody* first, RigidBody* second,
						 real friction, real restitution);

		/** Get the friction constant. */
		real getFriction() const;
		/** Get the restitution constant. */
		real getRestitution() const;

		/** */
		glm::vec3 getContactVelocity() const;
		void setContactVelocity(const glm::vec3& velocity);

		/**  */
		real getDesiredDeltaVelocity() const;

		void calculateInternals(real duration);
		void calculateDesiredDeltaVelocity(real duration);

		const glm::vec3& getRelativeContactPosition(int index) const;

		const glm::mat3& getContactToWorld() const;

	private:
		glm::vec3 calculateLocalVelocity(unsigned bodyIndex, real duration);
		
		void calculateContactBasis();


		CollisionPair m_pair{};

		glm::vec3 m_contactPoint{};
		glm::vec3 m_contactNormal{};
		real m_penetration{};

		

		real m_friction;
		real m_restitution;

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
