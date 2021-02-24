#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

#include <utility>

namespace r3
{
	class Particle;

	/**
	 * \brief A ParticleContact contains contact information of two
	 * particles.
	 */
	class R3D_DECLSPEC ParticleContact
	{
	public:
		explicit ParticleContact() = default;
		~ParticleContact() = default;

		/**
		 * \brief Initialize the contact.
		 * \param first First particle of the contact.
		 * \param second Second particle of the contact.
		 */
		void init(Particle* first, Particle* second);

		/**
		 * \brief Calculate the separating velocity.
		 * \return The separating velocity.
		 */
		real calculateSeparatingVelocity() const;

		/**
		 * \brief Resolve velocity and interpenetration.
		 * \param duration The amount of time, which has passed.
		 */
		void resolve(real duration);

		/** 
		 * \brief Get the contact's particles.
		 * \return The particles.
		 */
		std::pair<Particle*, Particle*>& getParticles();
		const std::pair<Particle*, Particle*>& getParticles() const;

		/**
		 * \brief Set the contact's contact normal.
		 * \param normal The contact normal.
		 */
		void setContactNormal(const glm::vec3& normal);
		/**
		 * \brief Get the contact's contact normal.
		 * \return The current contact normal.
		 */
		const glm::vec3& getContactNormal() const;

		/**
		 * \brief Set the contact's restitution.
		 * \param restitution The restitution.
		 */
		void setRestitution(real restitution);
		/**
		 * \brief Get the contact's restitution.
		 * \return The current restitution.
		 */
		real getRestitution() const;

		/**
		 * \brief Set the contact's penetration.
		 * \param penetration The penetration.
		 */
		void setPenetration(real penetration);
		/**
		 * \brief Change the contact's penetration
		 * \
		 */
		void addToPenetration(real summand);
		/**
		 * \brief Get the contact's penetration.
		 * \return The current penetration.
		 */
		real getPenetration() const;

		/**
		 * \brief Access to the first particle.
		 * \return The first particle.
		 */
		Particle* getFirst() const;
		/**
		 * \brief Access to the second particle.
		 * \return The second particle.
		 */
		Particle* getSecond() const;

		const glm::vec3* getParticleMovement() const;

	private:
		/**
		 * \brief Resolve the velocity for the particles.
		 * \param duration Time step of this update.
		 */
		void resolveVelocity(real duration);
		/**
		 * \brief Resolve the interpenetration of the particles.
		 * \param duration Time step of this update.
		 */
		void resolveInterpenetration(real duration);

		std::pair<Particle*, Particle*> m_particles{};
		real m_restitution{};
		glm::vec3 m_contactNormal;
		real m_penetration{};
		glm::vec3 m_particlesMovement[2]; // \todo
	};
}
