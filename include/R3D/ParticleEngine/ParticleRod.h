#pragma once
#include "ParticleLink.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ParticleContact;

	/**
	 * \brief Abstract class, which creates a distance constraint 
	 * between two particles. A contact gets created if this constraint
	 * is not fulfilled.
	 */
	class R3D_DECLSPEC ParticleRod : public ParticleLink
	{
	public:
		explicit ParticleRod(real length);
		virtual ~ParticleRod();

		/**
		* \brief Generate new contacts.
		* \param contactData Out parameter in which new contacts are added.
		*/
		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;

		/** \brief Set the current length of the rod. */
		void setLength(real length);

	protected:

		real m_length{};
	};
}