#pragma once
#include "R3D/Common/Common.h"
#include "ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class Particle;
	
	class R3D_DECLSPEC ParticleDrag : public ParticleForceGenerator
	{
	public:
		ParticleDrag(real k1, real k2);
		~ParticleDrag();

		void updateForce(Particle * particle, real duration) override;

	protected:
		real m_k1;
		real m_k2;
	};
}