#pragma once
#include "ParticleLink.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class ParticleContact;
	
	class ParticleCable : public ParticleLink
	{
	public:
		explicit ParticleCable();
		~ParticleCable();

		virtual unsigned int addContact(ParticleContact* contact, unsigned int limit) const override;
		void setMaxLength(real maxLength);
		void setRestitution(real restitution);

	protected:
		real m_maxLength;
		real m_restitution;
	};
}

