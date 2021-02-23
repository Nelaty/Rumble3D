#include "R3D/ParticleEngine/ParticleCable.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <glm/glm.hpp>

namespace r3
{

	ParticleCable::ParticleCable(const real maxLength, const real restitution)
		: m_maxLength{maxLength},
		m_restitution{restitution}
	{
	}

	void ParticleCable::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		const auto length = currentLength();
		if (length < m_maxLength)
		{
			return;
		}

		// Get an unused contact
		auto contact = contactData.getAvailableEntry();
		if (m_particles.second->hasFiniteMass())
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

		// 
		contact->setContactNormal(normal);
		contact->setPenetration(length - m_maxLength);
		contact->setRestitution(m_restitution);
	}
	
	void ParticleCable::setMaxLength(const real maxLength)
	{
		m_maxLength = maxLength;
	}
	
	void ParticleCable::setRestitution(const real restitution)
	{
		m_restitution = restitution;
	}
}