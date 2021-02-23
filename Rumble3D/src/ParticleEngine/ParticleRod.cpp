#include "R3D/ParticleEngine/ParticleRod.h"
#include "R3D/ParticleEngine/ParticleContact.h"
#include "R3D/ParticleEngine/Particle.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

namespace r3
{
	void ParticleRod::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		// Distance between particles
		const auto length = currentLength();

		// Particle distance is already perfect
		if(length == m_length) 
		{
			return;
		}

		// Get an available contact
		auto contact = contactData.getAvailableEntry();	
		if(m_particles.second->hasFiniteMass())
		{
			contact->init(m_particles.first, m_particles.second);
		}
		else 
		{
			contact->init(m_particles.first, nullptr);
		}

		// Negative contact normal
		auto normal = m_particles.second->getPosition() - m_particles.first->getPosition();
		normal = glm::normalize(normal);

		if(length > m_length)
		{
			contact->setContactNormal(normal);
			contact->setPenetration(length - m_length);
		}
		else 
		{
			contact->setContactNormal(-normal);
			contact->setPenetration(m_length - length);
		}

		// No bouncing
		contact->setRestitution(0);
	}

	void ParticleRod::setLength(real length)
	{
		m_length = length;
	}

	ParticleRod::ParticleRod(real length)
	{
		m_length = length;
	}
}

#undef GLM_ENABLE_EXPERIMENTAL