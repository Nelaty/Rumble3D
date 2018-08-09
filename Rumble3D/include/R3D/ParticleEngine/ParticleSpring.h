#pragma once
#include "ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class Particle;

	class ParticleSpring : public ParticleForceGenerator
	{	
	public:
		ParticleSpring(Particle* other, real springConstant, real restLength);
		~ParticleSpring();

		virtual void UpdateForce(Particle* particle, real duration);

	protected:
		Particle* m_other; //das andere Teilchen.
		real m_springConstant;
		real m_restLength;
	};
}