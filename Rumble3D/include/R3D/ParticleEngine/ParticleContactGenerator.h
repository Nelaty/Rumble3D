#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3 
{
	class ParticleContact;

	/**
	 * \brief Interface for contact generators for particles.
	 */
	class R3D_DECLSPEC ParticleContactGenerator
	{
	public:
		virtual ~ParticleContactGenerator();

		/**
		* \brief Generate new contacts.
		* \param contactData Out parameter in which new contacts are added.
		*/
		virtual void addContact(FixedSizeContainer<ParticleContact>& contactData) const = 0;

	protected:
		explicit ParticleContactGenerator();
	};
}