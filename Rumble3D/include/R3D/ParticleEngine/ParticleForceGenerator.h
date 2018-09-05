#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;

	/**
	 * Interface for force generators.
	 */
	class R3D_DECLSPEC ParticleForceGenerator
	{
	public:
		virtual ~ParticleForceGenerator();

		/** Schnittstellen-Methode, die im speziellen Kraft-Generator 
		 überladen werden muss. Die Methode berechnet und aktualisiert
		 die Kraft, die auf das Teilchen particle in der Zeitscheibe 
		 duration wirkt.
		*/
		virtual void updateForce(Particle* particle, real duration) = 0;

	protected:
		explicit ParticleForceGenerator();
	};
}