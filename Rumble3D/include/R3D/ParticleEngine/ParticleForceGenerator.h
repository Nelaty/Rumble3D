#pragma once
#include "R3D/Common/Precision.h"

//Schnittstellen-Klasse für Kraft-Generatoren
namespace rum
{
	class Particle;

	class ParticleForceGenerator
	{
	public:
		virtual ~ParticleForceGenerator();

		// Schnittstellen-Methode, die im speziellen Kraft-Generator 
		// überladen werden muss. Die Methode berechnet und aktualisiert
		// die Kraft, die auf das Teilchen particle in der Zeitscheibe 
		// duration wirkt.
		virtual void updateForce(Particle* particle, real duration) = 0;

	protected:
		explicit ParticleForceGenerator();
	};
}