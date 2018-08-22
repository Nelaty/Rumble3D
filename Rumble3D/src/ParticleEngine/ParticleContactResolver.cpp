#include "R3D/ParticleEngine/ParticleContactResolver.h"
#include "R3D/ParticleEngine/ParticleContact.h"

namespace rum
{
	ParticleContactResolver::ParticleContactResolver(unsigned int iterations)
		: m_iterations{iterations},
		m_iterationsUsed{0}
	{
	}

	ParticleContactResolver::~ParticleContactResolver()
	{
	}

	void ParticleContactResolver::setIterations(unsigned int iterations)
	{
		m_iterations = iterations;
	}

	void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned int numberOfContacts, real duration)
	{
		unsigned i;
		m_iterationsUsed = 0;
		while (m_iterationsUsed < m_iterations) 
		{
			// Suche den Kontakt mit kleinster Trennungsgeschwindigkeit
			// gleich größter Kollisionsgeschwindigkeit:
			real max = EROS_REAL_MAX;
			unsigned maxIndex = numberOfContacts;
			for (i = 0; i < numberOfContacts; ++i)
			{
				real separationVelocity = contactArray[i].calculateSeparatingVelocity();
				if (separationVelocity < max &&
					(separationVelocity < 0 || contactArray[i].m_penetration > 0)) 
				{
					max = separationVelocity;
					maxIndex = i;
				}
			}
			// wenn nichts zu behandeln ist:
			if(maxIndex == numberOfContacts)
			{
				break;
			}

			// Behandle den physikalisch interessantesten Kontakt:
			contactArray[maxIndex].resolve(duration);
			
			// Behandlung der Durchdringung:
			glm::vec3* move = contactArray[maxIndex].m_particlesMovement;
			for (i = 0; i < numberOfContacts; ++i)
			{
				if (contactArray[i].m_particles[0] == contactArray[maxIndex].m_particles[0])
				{
					contactArray[i].m_penetration -= glm::dot(move[0], contactArray[i].m_contactNormal);
				}
				else if (contactArray[i].m_particles[0] == contactArray[maxIndex].m_particles[1])
				{
					contactArray[i].m_penetration -= glm::dot(move[1], contactArray[i].m_contactNormal);
				}
				if (contactArray[i].m_particles[1])
				{
					if (contactArray[i].m_particles[1] == contactArray[maxIndex].m_particles[0])
					{
						contactArray[i].m_penetration += glm::dot(move[0], contactArray[i].m_contactNormal);
					}
					else if (contactArray[i].m_particles[1] == contactArray[maxIndex].m_particles[1])
					{
						contactArray[i].m_penetration += glm::dot(move[1], contactArray[i].m_contactNormal);
					}
				}
			}
			
			m_iterationsUsed++;
		}
	}
}