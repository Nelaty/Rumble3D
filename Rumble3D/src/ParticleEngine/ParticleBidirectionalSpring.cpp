#include "R3D/ParticleEngine/ParticleBidirectionalSpring.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleBidirectionalSpring::ParticleBidirectionalSpring(Particle* other, 
															 const real springConstant, 
															 const real restLength)
		: m_other(other),
		m_springConstant(springConstant),
		m_restLength(restLength)
	{
	}

	ParticleBidirectionalSpring::~ParticleBidirectionalSpring()
	{
	}

	void ParticleBidirectionalSpring::updateForce(Particle* particle, 
												  const real duration)
	{
		// Vektor der Feder
		auto force = particle->getPosition();
		force -= m_other->getPosition();

		// Kraft berechnen:
		auto magnitude = glm::length(force);
		if(magnitude == real(0))
		{
			return;
		}
		magnitude -= m_restLength;
		magnitude *= m_springConstant;

		//Resultierende Federkraft und Anwendung auf Teilchen:
		force = glm::normalize(force);
		force *= -magnitude;
		
		particle->addForce(force);
		m_other->addForce(-force);
	}
}
