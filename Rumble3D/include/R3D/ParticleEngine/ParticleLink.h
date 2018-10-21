#pragma once
#include "ParticleContactGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;
	class ParticleContact;

	/**
	 * \brief Abstract class. A ParticleLink links two particles.
	 */
	class R3D_DECLSPEC ParticleLink : public ParticleContactGenerator
	{
	public:
		virtual ~ParticleLink();

		// geerbte abstrakte Methode addContact zur 
		// Erinnerung auch hierher kopiert:
		unsigned int addContact(ParticleContact* contact, unsigned int limit) const override = 0;

		/**
		 * \brief Change the referenced particles
		 * \param first First particle
		 * \param second Second particle
		 */
		void setParticles(Particle* first, Particle* second);
	
	protected:
		explicit ParticleLink();

		/**
		 * \brief Calculate the length between the current particles.
		 * \return The calculated length.
		 */
		real currentLength() const;

		Particle* m_particles[2]{};		
	};
}
