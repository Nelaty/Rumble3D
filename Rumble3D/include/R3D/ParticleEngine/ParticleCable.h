#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/ParticleLink.h"

namespace r3
{
	class ParticleContact;

	/**
	 * \brief A ParticleCable is a contact generator, which will 
	 * generate a contact if particles are too far apart.
	 */
	class R3D_EXPORT ParticleCable : public ParticleLink
	{
	public:
		/**
		 * \brief ParticleCable constructor
		 * \param maxLength The maximal length of the cable.
		 * \param restitution The restitution coefficient of generated 
		 * contacts.
		 */
		explicit ParticleCable(real maxLength = 1.0f, real restitution = 0.0f);
		~ParticleCable() = default;

		/**
		* \brief Generate new contacts.
		* \param contactData Out parameter in which new contacts are added.
		*/
		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;

		/**
		 * \brief Set the threshold at which contacts will be generated.
		 * \maxLength The maximal length of the cable.
		 */
		void setMaxLength(real maxLength);
		/**
		 * \brief Set the restitution of generated contacts.
		 * \restitution The restitution coefficient.
		 */
		void setRestitution(real restitution);

	protected:
		real m_maxLength;
		real m_restitution;
	};
}

