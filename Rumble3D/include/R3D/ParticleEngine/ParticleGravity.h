#pragma once
#include "R3D/Common/Common.h"
#include "ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class Particle;

	class R3D_DECLSPEC ParticleGravity : public ParticleForceGenerator
	{
	public:
		explicit ParticleGravity(const glm::vec3& gravity);
		~ParticleGravity();

		void updateForce(Particle* particle, real duration) override;

	protected:
		glm::vec3 m_gravity;
	};
}