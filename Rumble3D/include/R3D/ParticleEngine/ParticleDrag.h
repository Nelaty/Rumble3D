#pragma once
#include "ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class Particle;
	
	class ParticleDrag : public ParticleForceGenerator
	{
	public:
		ParticleDrag(real k1, real k2);
		~ParticleDrag();
	
		virtual void updateForce(Particle * particle, real duration);

	protected:
		real m_k1;
		real m_k2;
	};
}