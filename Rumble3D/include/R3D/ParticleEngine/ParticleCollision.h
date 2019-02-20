#pragma once
#include "R3D/Common/Common.h"
#include "ParticleLink.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

#include <functional>

namespace r3
{
	class Particle;

	class ParticleContact;
	
	/**
	 * \brief A ParticleCollision can maintains a certain distance
	 * between two particles. A contact will be generated if those
	 * particles are too close together.
	 */
	class R3D_DECLSPEC ParticleCollision : public ParticleLink
	{	
	public:
		using CollisionCallback = std::function<void(Particle* first,
													 Particle* second,
													 const glm::vec3& contactNormal)>;
	
		/**
		 * \brief ParticleCollision constructor.
		 * \param restitution The restitution of generated contacts.
		 * \param distance The minimal distance, which should be
		 * maintained.
		 * \param penetration \todo Why does this even exist? Just calculate interpenetration in contact generation.
		 */
		explicit ParticleCollision(real restitution, real distance, real penetration);
		~ParticleCollision();

		/**
		 * \brief Generate new contacts.
		 * \param contactData Out parameter in which new contacts are added.
		 */
		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;

		/** \brief Set a callback for when a collision happens. */
		void setCollisionCallback(const CollisionCallback& callback);

	protected:
		real m_restitution;
		real m_distance;
		real m_penetration;

		CollisionCallback m_callback;
	};
	
}
