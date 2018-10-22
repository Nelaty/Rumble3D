#pragma once
#include "R3D/Common/Common.h"
#include "ParticleLink.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ParticleContact;
	
	/**
	 * \brief A ParticleCollision can maintains a certain distance
	 * between two particles. A contact will be generated if those
	 * particles are too close together.
	 */
	class R3D_DECLSPEC ParticleCollision : public ParticleLink
	{	
	public:
		/**
		 * \brief ParticleCollision constructor.
		 * \param restitution The restitution of generated contacts.
		 * \param distance The minimal distance, which should be
		 * maintained.
		 * \param penetration \todo Why does this even exist? Just calculate interpenetration in contact generation.
		 */
		explicit ParticleCollision(real restitution, real distance, real penetration);
		~ParticleCollision();

		/**
		* \brief Generate new contacts.
		* \param contactData Out parameter in which new contacts are added.
		*/
		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;
	
	protected:
		real m_restitution;
		real m_distance;
		real m_penetration;
	};
	
}
