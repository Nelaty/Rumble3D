#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionResolution/ICollisionResolutionFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Specialized collision resolution filter, which changes
	 * body velocities for bodies involved in contacts.
	 */
	class R3D_DECLSPEC VelocityResolver : public ICollisionResolutionFilter
	{
	public:
		explicit VelocityResolver();
		~VelocityResolver() = default;

		void resolve(FixedSizeContainer<Contact>& collisionData,
					 real timeDelta) override;

		void setMaxIterations(unsigned int iterations);
		void setVelocityEpsilon(real epsilon);

	private:
		glm::vec3 calculateFrictionlessImpulse(const Contact& contact,
											   glm::mat3 inverseInertiaTensor[2]) const;
		glm::vec3 calculateFrictionImpulse(const Contact& contact,
										   glm::mat3 inverseInertiaTensor[2]) const;


		void adjustVelocities(FixedSizeContainer<Contact>& collisionData, real duration);

		void applyVelocityChange(const Contact& contact,
								 glm::vec3 velocityChange[2],
								 glm::vec3 rotationChange[2]) const;

		real m_epsilon;

		unsigned int m_iterationsUsed;
		unsigned int m_iterationsMax;
	};
}