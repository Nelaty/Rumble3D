#include "R3D/ParticleEngine/ParticleSpring.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace r3
{
	ParticleSpring::ParticleSpring(Particle* other, 
								   const real springConstant,
								   const real restLength)
		: m_springConstant{springConstant},
		m_restLength{restLength},
		m_other{other}
	{
	}
	
	ParticleSpring::~ParticleSpring()
	= default;

	void ParticleSpring::updateForce(Particle* particle, real duration)
	{
		// Vektor der Feder
		auto force = particle->getPosition();
		force -= m_other->getPosition();
	
		// Kraft berechnen:
		auto magnitude = glm::length(force);
		magnitude -= m_restLength;
		magnitude *= m_springConstant;
	
		//Resultierende Federkraft und Anwendung auf Teilchen:
		force = glm::normalize(force);
		force *= -magnitude;
		particle->addForce(force);
	}
}