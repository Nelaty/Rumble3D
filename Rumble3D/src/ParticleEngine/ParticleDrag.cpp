#include "R3D/ParticleEngine/ParticleDrag.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
	ParticleDrag::ParticleDrag(real k1, real k2)
	{
		m_k1 = k1;
		m_k2 = k2;
	}
	
	ParticleDrag::~ParticleDrag()
	{
	}

	void ParticleDrag::updateForce(Particle * particle, real duration){
		glm::vec3 force = particle->getVelocity();
	
		real dragCoefficient = glm::length(force);
		dragCoefficient = m_k1 * dragCoefficient + m_k2 * dragCoefficient * dragCoefficient;
	
		force = glm::normalize(force);
		force *= -dragCoefficient;
		particle->addForce(force);
	}
}
