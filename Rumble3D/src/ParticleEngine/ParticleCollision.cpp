#include "R3D/ParticleEngine/ParticleCollision.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

namespace rum
{
	ParticleCollision::ParticleCollision(real restitution, real distance, real penetration) 
		: m_restitution(restitution), 
		m_distance(distance), 
		m_penetration(penetration)
	{
	}
	
	
	ParticleCollision::~ParticleCollision()
	{
	}
	
	unsigned int ParticleCollision::addContact(ParticleContact* contact, unsigned limit) const 
	{
		// Entfernung der Teilchen:
		real length = currentLength();
	
		// Wenn wir nicht zu nah sind, nichts tun:
		if (length > m_distance) { 
			return 0;
		}
	
		// Sonst Kontakt erzeugen und einfügen:
		contact->m_particles[0] = m_particles[0];
		contact->m_particles[1] = m_particles[1];
	
		// Negative Kontaktnormale:
		glm::vec3 normal = m_particles[1]->GetPosition() - m_particles[0]->GetPosition();
		normal *= (-1);
		normal = glm::normalize(normal);
	
		contact->setContactNormal(normal);
		contact->setPenetration(m_penetration);
		contact->setRestitution(m_restitution);
	
		return 1;
	}
}