#pragma once
#include "R3D/Common/Common.h"
#include "R3D/ParticleEngine/ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;

	class R3D_DECLSPEC ParticleBungee : public ParticleForceGenerator
	{
	public:
		explicit ParticleBungee(Particle* other, real springConstant, real restLength);
		~ParticleBungee();

		void updateForce(Particle* particle, real duration) override;

	protected:
		Particle* m_other;
		real m_springConstant;
		real m_restLength;
	};
}

