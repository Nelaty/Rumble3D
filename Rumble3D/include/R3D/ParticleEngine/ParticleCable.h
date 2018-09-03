#pragma once
#include "R3D/Common/Common.h"
#include "ParticleLink.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ParticleContact;
	
	class R3D_DECLSPEC ParticleCable : public ParticleLink
	{
	public:
		explicit ParticleCable();
		~ParticleCable();

		unsigned int addContact(ParticleContact* contact, unsigned int limit) const override;
		void setMaxLength(real maxLength);
		void setRestitution(real restitution);

	protected:
		real m_maxLength;
		real m_restitution;
	};
}

