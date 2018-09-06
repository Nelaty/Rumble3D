#pragma once
#include "R3D/Common/Common.h"
#include "ParticleContactGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

/*
*  Abstract class which links a particle with a static
*  position.
*/

namespace r3
{
	class Particle;

	class R3D_DECLSPEC ParticleConstraint : public ParticleContactGenerator
	{
	public:
		virtual ~ParticleConstraint();

	protected:
		explicit ParticleConstraint();

		real currentLength() const;

		glm::vec3 m_anchor;
		Particle* m_particle{};
	};
}
