#include "R3D/ParticleEngine/ParticleConstraint.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
	real ParticleConstraint::currentLength() const
	{
		glm::vec3 distance = m_particle->getPosition() - m_anchor;
		return glm::length(distance);
	}
}
