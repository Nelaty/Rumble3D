#pragma once
#include "ParticleContactGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

/*
*  Abstract class which links a particle with a static
*  position.
*/

namespace rum
{
	class Particle;
	class ParticleContact;

	class ParticleConstraint :	public ParticleContactGenerator
	{
	public:
		virtual ~ParticleConstraint();

	protected:
		explicit ParticleConstraint();

		real CurrentLength() const;

		glm::vec3 m_anchor;
		Particle* m_particle;
	};
}
