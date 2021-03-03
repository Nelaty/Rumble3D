#include "R3D/ParticleEngine/ParticleSpringBase.h"
#include <iostream>
namespace r3
{
	void ParticleSpringBase::setRestLength(real restLength)
	{
		m_restLength = restLength;
	}

	r3::real ParticleSpringBase::getRestLength() const
	{
		return m_restLength;
	}

	void ParticleSpringBase::setSpringConstant(real constant)
	{
		m_springConstant = constant;
	}

	r3::real ParticleSpringBase::getSpringConstant() const
	{
		return m_springConstant;
	}

	ParticleSpringBase::ParticleSpringBase(real springConstant,
										   real restLength)
		: m_springConstant(springConstant),
		m_restLength(restLength)
	{
	}

	bool ParticleSpringBase::isMagnitudeValid(const glm::vec3& target,
											  const glm::vec3& source,
											  glm::vec3& distance,
											  real& magnitude) const
	{
		// Force direction of zero vector is undefined
		distance = target - source;
		magnitude = glm::length(distance);
		return magnitude != real(0);
	}

	glm::vec3 ParticleSpringBase::calculateForce(glm::vec3 distance,
												 real magnitude) const
	{
		// a) Force only acts at a different distance than the resting length
		// b) A firm spring (higher constant) is more sensitive to changes in
		// the resting length
		magnitude = m_springConstant * (m_restLength - magnitude);

		distance = glm::normalize(distance);
		return distance * magnitude;
	}

}