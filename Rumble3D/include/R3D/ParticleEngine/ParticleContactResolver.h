#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ParticleContact;

	/**
	 * \brief A ParticleContactResolver resolves a given number of contacts.
	 */
	class R3D_DECLSPEC ParticleContactResolver
	{
	public:
		explicit ParticleContactResolver(unsigned int iterations);
		~ParticleContactResolver();

		/**
		 * \brief Set maximal number of iterations used. 
		 * \param iterations The new maximal number of iterations.
		 */
		void setIterationsMax(unsigned int iterations);
	
		/** 
		 * \brief Resolve collision and penetration. 
		 * \param contactArray The contacts to be resolved.
		 * \param numberOfContacts Number of contacts in the array.
		 * \param duration Time step used for this update.
		 */
		void resolveContacts(ParticleContact* contactArray,
							 unsigned int numberOfContacts,
							 real duration);

	protected:
		unsigned m_iterationsMax;
		unsigned m_iterationsUsed;
	};
}