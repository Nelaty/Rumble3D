#pragma once
#include "ParticleForceGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;

	class R3D_DECLSPEC ParticleSpring : public ParticleForceGenerator
	{	
	public:
		ParticleSpring(Particle* other, real springConstant, real restLength);
		~ParticleSpring();

		void updateForce(Particle* particle, real duration) override;

	protected:
		/** The other particle, this particle is connected to. */
		Particle* m_other;
		real m_springConstant;
		real m_restLength;
	};
}