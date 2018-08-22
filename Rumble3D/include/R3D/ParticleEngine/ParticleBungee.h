#pragma once
#include "R3D/ParticleEngine/ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class Particle;

	class ParticleBungee : public ParticleForceGenerator
	{
	public:
		explicit ParticleBungee(Particle* other, real springConstant, real restLength);
		~ParticleBungee();

		virtual void updateForce(Particle* particle, real duration);

	protected:
		Particle* m_other; //das andere Teilchen.
		real m_springConstant;
		real m_restLength;
	};
}

