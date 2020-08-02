#include "R3D/ParticleEngine/ParticlePlaneContactGenerator.h"
#include "R3D/ParticleEngine/ParticleContact.h"

namespace r3
{
	ParticlePlaneContactGenerator::ParticlePlaneContactGenerator(real restitution,
																 real radius)
		: m_restitution(restitution),
		m_radius(radius)
	{
	}

	ParticlePlaneContactGenerator::~ParticlePlaneContactGenerator()
	{
	}

	void ParticlePlaneContactGenerator::addContact(FixedSizeContainer<ParticleContact>& contactData) const
	{
		assert(m_particle && m_plane);

		// Calculate the distance between particle and plane
		const auto& position = m_particle->getPosition();
		auto normal = m_plane->getNormal();

		const auto centerDistance = glm::dot(normal, position) - m_plane->getOffset();

		// Distance greater than radius?
		if(centerDistance * centerDistance > m_radius * m_radius)
		{
			return;
		}

		// Check on which side of the plane the particle is.
		auto penetration = -centerDistance;
		if(centerDistance < 0)
		{
			normal *= -1;
			penetration *= -1;
		}
		penetration += m_radius;

		// Get an available contact and initialize it
		auto contact = contactData.getAvailableEntry();
		contact->init(m_particle, nullptr);
		contact->setContactNormal(normal);
		contact->setPenetration(penetration);
		contact->setRestitution(m_restitution);
	}

	void ParticlePlaneContactGenerator::setRestitution(real restitution)
	{
		m_restitution = restitution;
	}

	void ParticlePlaneContactGenerator::setPlane(CollisionPlane* plane)
	{
		m_plane = plane;
	}

	void ParticlePlaneContactGenerator::setParticle(Particle* particle)
	{
		m_particle = particle;
	}
}
