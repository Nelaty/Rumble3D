#pragma once
#include "R3D/Common/Precision.h"

namespace rum
{
	class ParticleContact;

	class ParticleContactResolver
	{
	public:
		explicit ParticleContactResolver(unsigned int iterations);
		~ParticleContactResolver();

		/** Set the number of iterations after creation. */
		void setIterations(unsigned int iterations);
	
		/** Resolve collision and penetration. */
		void resolveContacts(ParticleContact* contactArray,
							 unsigned int numberOfContacts,
							 real duration);

	protected:
		unsigned m_iterations;
		unsigned m_iterationsUsed; // Zum Tracking der Performanz;
	};
}