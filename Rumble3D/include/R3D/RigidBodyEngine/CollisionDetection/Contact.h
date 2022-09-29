#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPair.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	/**
	 * \brief A Contact represents a point in space at which two 
	 * rigid bodies collide. It is not a point in world space but 
	 * rather knows the relative offsets to the points of mass of 
	 * both rigid bodies.
	 */
	class R3D_EXPORT Contact
	{
	public:
		explicit Contact();
		~Contact() = default;

		/** 
		 * \brief Get the first colliding rigid body. 
		 * \return The first rigid body
		 */
		RigidBody* getFirst() const;
		/**
		 * \brief Get the second colliding rigid body. 
		 * \return The second rigid body
		 */
		RigidBody* getSecond() const;

		/** 
		 * Get a rigid body by index.
		 * \return The first body if index == 0, the second one if index == 1. 
		 */
		RigidBody* getBody(int index) const;

		/** 
		 * \brief Set the contact point.
		 * \param contactPoint Point, where the collision took place.
		 */
		void setContactPoint(const glm::vec3& contactPoint);
		/** 
		 * \brief Get the point, where the collision took place. 
		 * \return The contact point
		 */
		const glm::vec3& getContactPoint() const;

		/** 
		 * \brief Set the contact normal.
		 * \param contactNormal Direction of the collision at the contact point
		 */
		void setContactNormal(const glm::vec3& contactNormal);
		/**
		 * \brief Get the contact normal.
		 * \return The direction of the collision at the contact point
		 */
		glm::vec3 getContactNormal() const;

		/** 
		 * \brief Set the amount of interpenetration.
		 * \param penetration Interpenetration along the contact normal 
		 */
		void setPenetration(real penetration);
		/** 
		 * \brief Get the amount of interpenetration. 
		 * \return The amount of interpenetration
		 */
		real getPenetration() const;

		/**
		 * \brief Initialize this contact 
		 * \param first First colliding body
		 * \param second Second colliding body
		 */
		void setBodyData(RigidBody* first, RigidBody* second);

		/** 
		 * \brief Get the friction constant used for the bodies in 
		 * this contact. 
		 * \return The friction constant
		 */
		real getFriction() const;
		/**
		 * \brief Get the restitution constant used for the bodies in
		 * this contact.
		 * \return The restitution constant
		 */
		real getRestitution() const;

		/** 
		 * \brief Get the direction and magnitude of the velocity at 
		 * which both bodies collided.
		 * \return The closing velocity
		 */
		glm::vec3 getClosingVelocity() const;
		/**  
		 * \brief Set the closing velocity at which both bodies collide.
		 * \param velocity The closing velocity
		 */
		void setClosingVelocity(const glm::vec3& velocity);

		/**
		 * \brief Prepares this contact for collision resolution
		 * \details Assures that the first rigid body has no infinite
		 * mass and swaps it with the second one if necessary. It also
		 * calculates the desired delta velocity for this contact
		 * as well as the contact velocity and relative contact positions.
		 */
		void calculateInternals(real duration);
		/**
		 * \brief Calculate the needed velocity for this contact to
		 * combat vibrations.
		 */
		void calculateDesiredDeltaVelocity(real duration);

		/** 
		 * \brief Get the needed velocity for this contact to combat 
		 * vibrations.
		 * \return The desired velocity difference. 
		 */
		real getDesiredDeltaVelocity() const;
		/**
		 * \brief Get the contact position relative to the first or the
		 * second rigid body.
		 * \param index Either 0 (first body) or 1 (second body)
		 * \return The relative contact position
		 */
		const glm::vec3& getRelativeContactPosition(int index) const;

		/**
		 * \brief Get the rotation matrix, which transforms this contact to
		 * world orientation.
		 * \return The rotation matrix
		 */
		const glm::mat3& getContactToWorld() const;

		void matchAwakeState();

	private:
		glm::vec3 calculateLocalVelocity(unsigned bodyIndex, real duration);

		/**
		 * \brief Calculate the contact basis needed to transform contact
		 * coordinates into world space.
		 */
		void calculateContactBasis();

		/**
		 * \brief Swap first and second rigid body.
		 */
		void swapBodies();

		CollisionPair m_pair{};

		glm::vec3 m_contactPoint{};
		glm::vec3 m_contactNormal{};
		real m_penetration{};

		real m_friction;
		real m_restitution;

		/**
		* \brief Transform from contact space to world space.
		*/
		glm::mat3 m_contactToWorld{};
		glm::vec3 m_closingVelocity{};
		/**
		 * \brief Needed velocity to combat vibrations
		 */
		real m_desiredDeltaVelocity{};
		/**
		 * \brief Vectors from contact point to center of mass of rigid bodies
		*/
		glm::vec3 m_relativeContactPosition[2]{};

		static constexpr real s_velocityLimit = static_cast<real>(0.25);
	};
}
