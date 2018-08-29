#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class Particle;

	class R3D_DECLSPEC ParticleContact
	{
		// Die Resolver-Klasse muss ohne Unterlass die Attribute von ParticleContact
		// lesen und verändern. Der Code im Resolver würde mit gettern und settern
		// sehr unleserlich und schwer zu warten.
		friend class ParticleContactResolver;

	//protected: zu debugging zwecken!!!
	public:
		explicit ParticleContact();
		~ParticleContact();

		//Berechnung der Trennungsgeschwindigkeit für diesen Kontakt.
		real calculateSeparatingVelocity() const;

		// Behandlung der Geschwindigkeit und des Durchdringens.
		void resolve(real duration);

		// Gib den Array mit den Partikeln zurück:
		Particle * getParticles();
		void setContactNormal(glm::vec3 normal);
		void setRestitution(real restitution);
		void setPenetration(real penetration);



		Particle* m_particles[2]{};      // Die beiden am Kontakt beteiligten Teilchen.
		real m_restitution{};             // Wiederherstellungskoeffizient.
		glm::vec3 m_contactNormal;       // Kontaktnormale.
		real m_penetration{};             // Durchdringung bis zum Ende des Ticks.
		glm::vec3 m_particlesMovement[2];// Bewegung der Teilchen nach Durchdringung
		
	private:
		// Behandlung der Geschwindigkeit für diesen Kontakt.
		void resolveVelocity(real duration);
		// Behandlung der Durchdringung für diesen Kontakt.
		void resolveInterpenetration(real duration);
	};
}
