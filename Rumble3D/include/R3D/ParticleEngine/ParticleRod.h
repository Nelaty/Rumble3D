#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/ParticleLink.h"

namespace r3
{
	class ParticleContact;

	/**
	 * \brief Abstract class, which creates a distance constraint 
	 * between two particles. A contact gets created if this constraint
	 * is not fulfilled.
	 */
	class R3D_EXPORT ParticleRod : public ParticleLink
	{
	public:
		explicit ParticleRod(real length);
		virtual ~ParticleRod() = default;

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