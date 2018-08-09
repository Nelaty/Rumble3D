#include "R3D/ParticleEngine/ParticleSpring.h"
#include "R3D/ParticleEngine/Particle.h"

#include <glm/glm.hpp>

namespace rum
{
	ParticleSpring::ParticleSpring(Particle* other, real springConstant, real restLength)
		: m_other{other},
		m_springConstant{springConstant},
		m_restLength{restLength}
	{
	}
	
	ParticleSpring::~ParticleSpring()
	{
	}

	void ParticleSpring::UpdateForce(Particle* particle, real duration)
	{
		// Vektor der Feder
		glm::vec3 force = particle->GetPosition();
		force -= m_other->GetPosition();
	
		// Kraft berechnen:
		real magnitude = glm::length(force);
		magnitude -= m_restLength;
		magnitude *= m_springConstant;
	
		//Resultierende Federkraft und Anwendung auf Teilchen:
		force = glm::normalize(force);
		force *= -magnitude;
		particle->AddForce(force);
	}
}