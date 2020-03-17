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

	ParticleCable::~ParticleCable()
	= default;

	void ParticleCable::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		const auto length = currentLength();
		if(length < m_maxLength)
		{
			return;
		}

		// Get an unused contact
		auto contact = contactData.getAvailableEntry();
		contact->init(m_particles[0], m_particles[1]);

		// Negative contact normal
		auto normal = m_particles[1]->getPosition() - m_particles[0]->getPosition();
		normal = glm::normalize(normal);

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