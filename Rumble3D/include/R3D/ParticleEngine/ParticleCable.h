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

		unsigned int AddContact(ParticleContact* contact, unsigned int limit) const override;
		void SetMaxLength(real maxLength);
		void SetRestitution(real restitution);

	protected:
		real m_maxLength;
		real m_restitution;
	};
}

