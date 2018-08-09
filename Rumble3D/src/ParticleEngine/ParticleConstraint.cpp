#include "R3D/ParticleEngine/ParticleConstraint.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContact.h"

namespace rum
{

	ParticleConstraint::~ParticleConstraint()
	{
	}

	ParticleConstraint::ParticleConstraint()
	{
	}

	real ParticleConstraint::CurrentLength() const
	{
		glm::vec3 distance = m_particle->GetPosition() - m_anchor;
		return glm::length(distance);
	}
}
