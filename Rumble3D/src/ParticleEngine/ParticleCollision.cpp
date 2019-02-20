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
	
	ParticleCollision::~ParticleCollision()
	= default;

	void ParticleCollision::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		// Wenn wir nicht zu nah sind, nichts tun:
		if (currentLength() > m_distance)
		{
			return;
		}

		auto contact = contactData.getAvailableEntry();

		// Sonst Kontakt erzeugen und einfügen:
		contact->init(m_particles[0], m_particles[1]);

		// Negative Kontaktnormale:
		glm::vec3 normal = m_particles[1]->getPosition() - m_particles[0]->getPosition();
		normal *= -1;
		normal = glm::normalize(normal);

		contact->setContactNormal(normal);
		contact->setPenetration(m_penetration);
		contact->setRestitution(m_restitution);
	
		if(m_callback)
		{
			m_callback(m_particles[0], m_particles[1], normal);
		}
	}

	void ParticleCollision::setCollisionCallback(const CollisionCallback& callback)
	{
		m_callback = callback;
	}
}
