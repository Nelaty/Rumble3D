#include "R3D/ParticleEngine/ParticleCollision.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

namespace r3
{
	ParticleCollision::ParticleCollision(const real restitution, 
										 const real distance, 
										 const real penetration) 
		: m_restitution(restitution), 
		m_distance(distance), 
		m_penetration(penetration)
	{
	}

	void ParticleCollision::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		// Wenn wir nicht zu nah sind, nichts tun:
		if (currentLength() > m_distance)
		{
			return;
		}

		auto contact = contactData.getAvailableEntry();

		// Sonst Kontakt erzeugen und einf�gen:
		contact->init(m_particles.first, m_particles.second);

		// Negative Kontaktnormale:
		glm::vec3 normal = m_particles.second->getPosition() - m_particles.first->getPosition();
		normal *= -1;
		normal = glm::normalize(normal);

		contact->setContactNormal(normal);
		contact->setPenetration(m_penetration);
		contact->setRestitution(m_restitution);
	
		if(m_callback)
		{
			m_callback(m_particles.first, m_particles.second, normal);
		}
	}

	void ParticleCollision::setCollisionCallback(const CollisionCallback& callback)
	{
		m_callback = callback;
	}
}
