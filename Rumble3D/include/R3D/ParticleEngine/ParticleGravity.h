#pragma once
#include "ParticleForceGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class Particle;

	class ParticleGravity :	public ParticleForceGenerator
	{
	public:
		ParticleGravity(const glm::vec3& gravity);

		void updateForce(Particle* particle, real duration) override;

	protected:
		glm::vec3 m_gravity;
	};
}