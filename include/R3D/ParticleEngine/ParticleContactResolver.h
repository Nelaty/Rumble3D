#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include "R3D/Utility/FixedSizeContainer.h"

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
		* \param contactData The contacts to be resolved.
		* \param duration Time step used for this update.
		*/
		void resolveContacts(FixedSizeContainer<ParticleContact>& contactData,
							 real duration);

	protected:
		unsigned m_iterationsMax;
		unsigned m_iterationsUsed;
	};
}
