#pragma once
#include "R3D/Common/Precision.h"

#include <vector>

namespace rum
{
	class Particle;
	class ParticleForceGenerator;

	// Speichert alle Kraft-Generatoren und die Teilchen, auf denen
	// sie wirken.
	class ParticleForceRegistry
	{	
	public:
		// Registriert ein Paar aus Teilchen und Kraftgenerator, der
		// auf dem Teilchen wirkt.
		void add(Particle* particle, ParticleForceGenerator* fg);
		// Löscht einen Eintrag aus der Registry.
		void remove(Particle* particle, ParticleForceGenerator* fg);
		// Löscht alle Einträge aus der Registry.
		void clear();
		// Ruft alle Kraft-Generatoren auf, so dass diese die Kräfte
		// der zugehörenden Teilchen aktualisieren können.
		void updateForces(real duration);

	protected:
		// Ein Eintrag in der Registry:
		struct ParticleForceRegistrationEntry
		{
			Particle* m_particle;
			ParticleForceGenerator* m_forceGenerator;
		};

		// Die Registry:
		typedef std::vector<ParticleForceRegistrationEntry> Registry;
		Registry m_registrations;
	};
}

