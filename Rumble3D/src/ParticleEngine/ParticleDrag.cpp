#include "R3D/ParticleEngine/ParticleDrag.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleDrag::ParticleDrag(const real crossSectionalArea,
							   const real dragCoefficient, 
							   const real mediumDensity)
		: m_crossSectionalArea(crossSectionalArea),
		m_dragCoefficient(dragCoefficient),
		m_mediumDensity(mediumDensity)
	{
	}

	void ParticleDrag::updateForce(Particle* particle, 
								   const real duration)
	{
		auto force = particle->getVelocity();

		const auto magnitude = glm::length(force);
		if(magnitude == real(0))
		{
			return;
		}

		const auto dragCoefficient = 
			real(0.5) * m_crossSectionalArea * 
			m_dragCoefficient * m_mediumDensity * magnitude * magnitude;
	
		force = glm::normalize(force);
		force *= -dragCoefficient;
		particle->addForce(force);
	}
}