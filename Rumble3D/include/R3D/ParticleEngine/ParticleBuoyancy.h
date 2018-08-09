#pragma once
#include "R3D/ParticleEngine/ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class Particle;

	class ParticleBuoyancy : public ParticleForceGenerator
	{	
	public:
		explicit ParticleBuoyancy(real maxDepth, real volume, real liquidHeight, real liquidDensity = real(1000.0f));
		~ParticleBuoyancy();

		virtual void UpdateForce(Particle* particle, real duration);

	protected:
		real m_maxDepth;
		real m_volume;
		real m_liquidHeight;
		real m_liquidDensity;

	};
}