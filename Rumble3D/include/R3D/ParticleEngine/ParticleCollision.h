#pragma once
#include "ParticleLink.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class ParticleContact;

	class ParticleCollision : public ParticleLink
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
