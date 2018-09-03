#include "R3D/ParticleEngine/ParticleContact.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/gtc/constants.hpp>

namespace r3
{
	void ParticleContact::resolve(real duration)
	{
		resolveVelocity(duration);
		resolveInterpenetration(duration);
	}

	ParticleContact::ParticleContact()
	= default;

	ParticleContact::~ParticleContact()
	= default;

	real ParticleContact::calculateSeparatingVelocity() const
	{
		// v_s = (\dot{p_a} - \dot{p_b}) * (\hat{p_a -p_b})
		glm::vec3 relativeVelocity = m_particles[0]->getVelocity();
		if(m_particles[1])
		{
			relativeVelocity -= m_particles[1]->getVelocity();
		}
		return glm::dot(relativeVelocity, m_contactNormal);
	}

	void ParticleContact::resolveVelocity(real duration)
	{
		real separatingVelocity = calculateSeparatingVelocity();
		if (separatingVelocity > 0) 
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
		if(m_particles[1])
		{
			accelerationCausedVelocity -= m_particles[1]->getAcceleration();
		}
		// Skalarprodukt: wieviel der Beschleunigung wirkt in Richtung Kontaktnormale:
		real accelerationCausedSeparationVelocity =	glm::dot(accelerationCausedVelocity, m_contactNormal) * duration;
		// Falls wir eine Kollisionsgeschwindigkeit aufgrund der Beschleunigung haben, 
		// muss sie von der newSeparationVelocity abgezogen werden:
		if (accelerationCausedSeparationVelocity < 0) 
		{
			newSeparatingVelocity += m_restitution * accelerationCausedSeparationVelocity;
			// zuviel abgezogen?
			if (newSeparatingVelocity < 0) 
			{
				newSeparatingVelocity = 0;
			}
		}

		// Geschwindigkeit des Gesamtsystems
		real deltaVelocity = newSeparatingVelocity - separatingVelocity;

		// Veraenderung der Geschwindigkeit in Abh. der Massen der Teilchen
		real totalInverseMass = m_particles[0]->getInverseMass();
		if(m_particles[1])
		{
			totalInverseMass += m_particles[1]->getInverseMass();
		}
		// Fehler Millington: Massen und nicht 1/Masse nehmen!!!

		// Wenn beide Teilchen unendliche Masse, dann aendert Impuls nichts:
		if(!(m_particles[0]->hasFiniteMass()))
		{
			return;
		}
		// Gesamtimpuls g = (m_1 + m_2) * v 
		real impulse = deltaVelocity / totalInverseMass;

		// Impuls / inverse Masse in Richtung der Kontaktnormalen
		glm::vec3 impulsePerMass = m_contactNormal * impulse;

		// Anwendung des Impulses je Teilchen proportional zu den inversen Massen:
		// \prime{\hat{p}} = \dot{p} + 1/m * g
		m_particles[0]->setVelocity(m_particles[0]->getVelocity() +
									impulsePerMass * m_particles[0]->getInverseMass());

		if (m_particles[1]) 
		{
			// hier negativ, da aus Sicht von m_particles[0]
			m_particles[1]->setVelocity(m_particles[1]->getVelocity() +
										impulsePerMass * -m_particles[1]->getInverseMass()); 
		}
	}

	void ParticleContact::resolveInterpenetration(real duration)
	{
		// Ohne Durchdringung ist nichts zu tun:
		// Bislang wurde Durchdringung noch nicht berechnet!!!
		if(m_penetration <= 0)
		{
			return;
		}

		// m_a + m_b
		real totalMass = m_particles[0]->getMass();
		if(m_particles[1])
		{
			totalMass += m_particles[1]->getMass();
		}
		if(!m_particles[0]->hasFiniteMass())
		{
			return;
		}

		//Berechne d * n:
		glm::vec3 dn = m_contactNormal * m_penetration;

		// Berechne 1/(m_a + m_b) * d * n
		glm::vec3 movePerInverseMass = dn * ((real)1.0 / totalMass);

		// Berechnung von Delta-p_a und Delta-p_b
		m_particlesMovement[0] = movePerInverseMass * m_particles[0]->getMass();
		if (m_particles[1])
		{
			m_particlesMovement[1] = movePerInverseMass * -m_particles[1]->getMass();
		}
		else 
		{
			m_particlesMovement[1] = glm::vec3(0.0f);
		}

		// Anwendung der Aufloesung der Durchdringung:
		m_particles[0]->setPosition(m_particles[0]->getPosition() + m_particlesMovement[0]);
		if (m_particles[1])
		{
			m_particles[1]->setPosition(m_particles[1]->getPosition() + m_particlesMovement[1]);
		}
	}

	Particle * ParticleContact::getParticles()
	{
		return *m_particles;
	}

	void ParticleContact::setContactNormal(glm::vec3 normal)
	{
		m_contactNormal = normal;
	}

	void ParticleContact::setRestitution(real restitution)
	{
		m_restitution = restitution;
	}

	void ParticleContact::setPenetration(real penetration)
	{
		m_penetration = penetration;
	}
}