#pragma once
#include "ParticleContactGenerator.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class Particle;
	class ParticleContact;

	// Speichert zwei verbundene Teilchen.
	class ParticleLink : public ParticleContactGenerator
	{
	public:
		// geerbte abstrakte Methode addContact zur 
		// Erinnerung auch hierher kopiert:
		virtual unsigned int AddContact(ParticleContact* contact, unsigned int limit) const = 0;
		// Referenzen auf Teilchen übergeben:
		void setParticles(Particle* particle0, Particle* particle1 = 0);
	
	protected:
		// Abstand zwischen den verbundenen Teilchen.
		real currentLength() const;

		Particle* m_particles[2];		
	};
}
