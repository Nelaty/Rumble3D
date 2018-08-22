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
		virtual ~ParticleLink();

		// geerbte abstrakte Methode addContact zur 
		// Erinnerung auch hierher kopiert:
		unsigned int addContact(ParticleContact* contact, unsigned int limit) const override = 0;
		// Referenzen auf Teilchen übergeben:
		void setParticles(Particle* particle0, Particle* particle1 = nullptr);
	
	protected:
		explicit ParticleLink();

		// Abstand zwischen den verbundenen Teilchen.
		real currentLength() const;

		Particle* m_particles[2]{};		
	};
}
