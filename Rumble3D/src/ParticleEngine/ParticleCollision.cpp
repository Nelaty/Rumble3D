#include <R3D/ParticleEngine/ParticleCollision.h>
#include <R3D/ParticleEngine/Particle.h>
#include <R3D/ParticleEngine/ParticleContact.h>

namespace r3
{
	ParticleCollision::ParticleCollision(const real restitution, 
										 const real distance)
		: m_restitution(restitution), 
		m_distance(distance)
	{
	}

	void ParticleCollision::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
	    // Check if particles overlap
        real penetration = m_distance - currentLength();
		if (penetration <= 0) return;

		// Negative contact normal
		glm::vec3 normal = glm::normalize(m_particles.first->getPosition()
		                                  - m_particles.second->getPosition());

        auto contact = contactData.getAvailableEntry();
        contact->init(m_particles.first, m_particles.second);
		contact->setContactNormal(normal);
		contact->setPenetration(penetration);
		contact->setRestitution(m_restitution);
	
		if(m_callback) m_callback(m_particles.first, m_particles.second, normal);
	}

	void ParticleCollision::setCollisionCallback(const CollisionCallback& callback)
	{
		m_callback = callback;
	}
}
