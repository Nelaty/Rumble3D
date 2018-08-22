#pragma once
#include "ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class Particle;

	class ParticleAnchoredSpring : public ParticleForceGenerator
	{
	public:
		explicit ParticleAnchoredSpring(glm::vec3* anchor, real springConstant, real restLength);
		~ParticleAnchoredSpring();

		void updateForce(Particle* particle, real duration) override;
	
	protected:
		glm::vec3* m_anchor;
		real m_springConstant;
		real m_restLength;
	};
}