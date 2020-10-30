#include "R3D/ParticleEngine/ParticleContactResolver.h"
#include "R3D/ParticleEngine/ParticleContact.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
	ParticleContactResolver::ParticleContactResolver(const unsigned iterations)
		: m_iterationsMax{iterations},
		m_iterationsUsed{0}
	{
	}

	ParticleContactResolver::~ParticleContactResolver()
	= default;

	void ParticleContactResolver::setIterationsMax(const unsigned iterations)
	{
		m_iterationsMax = iterations;
	}

	void ParticleContactResolver::resolveContacts(FixedSizeContainer<ParticleContact>& contactData,
												  const real duration)
	{
		auto& contactArray = contactData.getData();
		const auto numberOfContacts = contactData.getEntriesUsed();

		m_iterationsUsed = 0;
		while (m_iterationsUsed < m_iterationsMax)
		{
			// Suche den Kontakt mit kleinster Trennungsgeschwindigkeit
			// gleich gr��ter Kollisionsgeschwindigkeit:
			auto max = R3D_REAL_MAX;
			auto maxIndex = numberOfContacts;
			for (unsigned i = 0; i < numberOfContacts; ++i)
			{
				const auto separationVelocity = contactArray[i].calculateSeparatingVelocity();
				if (separationVelocity < max &&
					(separationVelocity < 0 || contactArray[i].getPenetration() > 0))
				{
					max = separationVelocity;
					maxIndex = i;
				}
			}
			// wenn nichts zu behandeln ist:
			if (maxIndex == numberOfContacts)
			{
				break;
			}

			// Behandle den physikalisch interessantesten Kontakt:
			contactArray[maxIndex].resolve(duration);

			// Behandlung der Durchdringung:
			auto* firstMax = contactArray[maxIndex].getFirst();
			auto* secondMax = contactArray[maxIndex].getSecond();

			const auto move = contactArray[maxIndex].getParticleMovement();
			for (unsigned i = 0; i < numberOfContacts; ++i)
			{
				auto* first = contactArray[i].getFirst();
				auto* second = contactArray[i].getSecond();

				const auto& contactNormal = contactArray[i].getContactNormal();

				if (first == firstMax)
				{
					contactArray[i].addToPenetration(-glm::dot(move[0], contactNormal));
				}
				else if (first == secondMax)
				{
					contactArray[i].addToPenetration(-glm::dot(move[1], contactNormal));
				}
				if (second)
				{
					if (second == firstMax)
					{
						contactArray[i].addToPenetration(glm::dot(move[0], contactNormal));
					}
					else if (second == secondMax)
					{
						contactArray[i].addToPenetration(glm::dot(move[1], contactNormal));
					}
				}
			}

			m_iterationsUsed++;
		}
	}
}
