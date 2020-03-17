#include "R3D/ParticleEngine/ParticleRod.h"
#include "R3D/ParticleEngine/ParticleContact.h"
#include "R3D/ParticleEngine/Particle.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

namespace r3
{
	ParticleRod::~ParticleRod()
	= default;

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
		contact->init(m_particles[0], m_particles[1]);

		// Negative contact normal
		auto normal = m_particles[1]->getPosition() - m_particles[0]->getPosition();
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