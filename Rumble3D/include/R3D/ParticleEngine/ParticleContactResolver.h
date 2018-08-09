#pragma once
#include "R3D/Common/Precision.h"

namespace rum
{
	class ParticleContact;

	class ParticleContactResolver
	{
	public:
		ParticleContactResolver(unsigned int iterations);
		~ParticleContactResolver();
		
		//Setze Anzahl der Iterationen nach der Erzeugung:
		void SetIterations(unsigned int iterations);
	
		// Kollisions- und Durchdringungsbehandlung:
		void ResolveContacts(ParticleContact* contactArray, unsigned int numberOfContacts, real duration);

	protected:
		unsigned m_iterations;
		unsigned m_iterationsUsed; // Zum Tracking der Performanz;
	};
}