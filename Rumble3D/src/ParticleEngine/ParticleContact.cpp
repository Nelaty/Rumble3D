#include "R3D/ParticleEngine/ParticleContact.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/gtc/constants.hpp>

namespace r3
{
	void ParticleContact::resolve(const real duration)
	{
		resolveVelocity(duration);
		resolveInterpenetration(duration);
	}

	ParticleContact::ParticleContact()
	= default;

	ParticleContact::~ParticleContact()
	= default;

	void ParticleContact::init(Particle* first, Particle* second)
	{
		m_particles[0] = first;
		m_particles[1] = second;
	}

	real ParticleContact::calculateSeparatingVelocity() const
	{
		// v_s = (\dot{p_a} - \dot{p_b}) * (\hat{p_a -p_b})
		glm::vec3 relativeVelocity = m_particles[0]->getVelocity();
		if(m_particles[1]->hasFiniteMass())
		{
			relativeVelocity -= m_particles[1]->getVelocity();
		}
		return glm::dot(relativeVelocity, m_contactNormal);
	}

	void ParticleContact::resolveVelocity(const real duration)
	{
		const real separatingVelocity = calculateSeparatingVelocity();

		// If particles don't move, there's nothing to resolve
		if(separatingVelocity > 0) return;

		// Wenn beide Teilchen unendliche Masse, dann aendert Impuls nichts:
		if(!m_particles[0]->hasFiniteMass() && !m_particles[1]->hasFiniteMass())
		{
			return;
		}

		// \prime{v_s} = -c*v_s
		real newSeparatingVelocity = -separatingVelocity * m_restitution;

		// Einschub für die Beruecksichtigung von ruhenden Kontakten:
		// Prüfe Geschwindigkeit, die aus der Beschleunigung herruehrt:
		//ACHTUNG: Hier nicht berücksichtigt, dass Masse unendlich seinkann -> keine v aus der acc
		//DOCH: da hier particle[1] nicht gesetzt werden darf. ->> NULL und das wird geprüft.

		glm::vec3 accelerationCausedVelocity = m_particles[0]->getAcceleration();
		if(m_particles[1]->hasFiniteMass())
		{
			accelerationCausedVelocity -= m_particles[1]->getAcceleration();
		}
		// Skalarprodukt: wieviel der Beschleunigung wirkt in Richtung Kontaktnormale:
		real accelerationCausedSeparationVelocity = glm::dot(accelerationCausedVelocity, m_contactNormal) * duration;
		// Falls wir eine Kollisionsgeschwindigkeit aufgrund der Beschleunigung haben, 
		// muss sie von der newSeparationVelocity abgezogen werden:
		if(accelerationCausedSeparationVelocity < 0)
		{
			newSeparatingVelocity += m_restitution * accelerationCausedSeparationVelocity;
			// zuviel abgezogen?
			if(newSeparatingVelocity < 0)
			{
				newSeparatingVelocity = 0;
			}
		}

		// Geschwindigkeit des Gesamtsystems
		const real deltaVelocity = newSeparatingVelocity - separatingVelocity;

		// Veraenderung der Geschwindigkeit in Abh. der Massen der Teilchen
		real totalInverseMass = m_particles[0]->getInverseMass();
		if(m_particles[1]->hasFiniteMass())
		{
			totalInverseMass += m_particles[1]->getInverseMass();
		}

		// Gesamtimpuls g = (m_1 + m_2) * v 
		const real impulse = deltaVelocity / totalInverseMass;

		// Impuls / inverse Masse in Richtung der Kontaktnormalen
		const glm::vec3 impulsePerInverseMass = m_contactNormal * impulse;

		// Anwendung des Impulses je Teilchen proportional zu den inversen Massen:
		// \prime{\hat{p}} = \dot{p} + 1/m * g

		if(m_particles[0]->hasFiniteMass())
		{
			m_particles[0]->setVelocity(m_particles[0]->getVelocity() +
										impulsePerInverseMass * m_particles[0]->getInverseMass());
		}

		if(m_particles[1]->hasFiniteMass())
		{
			// hier negativ, da aus Sicht von m_particles[0]
			m_particles[1]->setVelocity(m_particles[1]->getVelocity() +
										impulsePerInverseMass * -m_particles[1]->getInverseMass());
		}
	}

	void ParticleContact::resolveInterpenetration(real duration)
	{
		// Ohne Durchdringung ist nichts zu tun:
		// Bislang wurde Durchdringung noch nicht berechnet!!!
		if(m_penetration <= 0) return;

		// Velocity change in accordance with their masses
		real totalInverseMass = m_particles[0]->getInverseMass();
		if(m_particles[1]->hasFiniteMass())
		{
			totalInverseMass += m_particles[1]->getInverseMass();
		}
		if(totalInverseMass <= 0) return;

		// Berechne 1/(m_a + m_b) * d * n
		glm::vec3 movePerInverseMass = m_contactNormal * (m_penetration / totalInverseMass);

		// Berechnung von Delta-p_a und Delta-p_b
		m_particlesMovement[0] = movePerInverseMass * m_particles[0]->getInverseMass();
		if (m_particles[1]->hasFiniteMass())
		{
			m_particlesMovement[1] = movePerInverseMass * -m_particles[1]->getInverseMass();
		}
		else 
		{
			m_particlesMovement[1] = glm::vec3(0);
		}

		// Anwendung der Aufloesung der Durchdringung:
		m_particles[0]->setPosition(m_particles[0]->getPosition() + m_particlesMovement[0]);
		if (m_particles[1]->hasFiniteMass())
		{
			m_particles[1]->setPosition(m_particles[1]->getPosition() + m_particlesMovement[1]);
		}
	}

	Particle* ParticleContact::getParticles()
	{
		return m_particles[0];
	}

	void ParticleContact::setContactNormal(const glm::vec3& normal)
	{
		m_contactNormal = normal;
	}

	const glm::vec3& ParticleContact::getContactNormal() const
	{
		return m_contactNormal;
	}

	void ParticleContact::setRestitution(const real restitution)
	{
		m_restitution = restitution;
	}

	real ParticleContact::getRestitution() const
	{
		return m_restitution;
	}

	void ParticleContact::setPenetration(const real penetration)
	{
		m_penetration = penetration;
	}

	void ParticleContact::addToPenetration(const real summand)
	{
		m_penetration += summand;
	}

	real ParticleContact::getPenetration() const
	{
		return m_penetration;
	}

	Particle* ParticleContact::getFirst() const
	{
		return m_particles[0];
	}

	Particle* ParticleContact::getSecond() const
	{
		return m_particles[1];
	}

	const glm::vec3* ParticleContact::getParticleMovement() const
	{
		return m_particlesMovement;
	}
}
