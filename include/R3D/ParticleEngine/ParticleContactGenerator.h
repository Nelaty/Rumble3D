#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3 
{
	class ParticleContact;

	/**
	 * \brief Interface for contact generators for particles.
	 */
	class ParticleContactGenerator
	{
	public:
		virtual ~ParticleContactGenerator();

		/**
		 * \brief Generate new contacts.
		 * \param contact Contact array which points to first element in the array.
		 * \param limit Maximal number, which the array can hold.
		 * \return The number of newly generated contacts.
		 */
		//virtual unsigned addContact(ParticleContact* contact, unsigned int limit) const = 0;

		/**
		* \brief Generate new contacts.
		* \param contactData Out parameter in which new contacts are added.
		*/
		virtual void addContact(FixedSizeContainer<ParticleContact>& contactData) const = 0;

	protected:
		explicit ParticleContactGenerator();
	};
}