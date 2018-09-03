#pragma once
#include "R3D/Common/Common.h"
#include "ParticleLink.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ParticleContact;

	class R3D_DECLSPEC ParticleCollision : public ParticleLink
	{
	
	public:
		explicit ParticleCollision(real restitution, real distance, real penetration);
		~ParticleCollision();

		unsigned int addContact(ParticleContact* contact, unsigned limit) const override;
	
	protected:
		real m_restitution;
		real m_distance;
		real m_penetration;
	};
	
}
