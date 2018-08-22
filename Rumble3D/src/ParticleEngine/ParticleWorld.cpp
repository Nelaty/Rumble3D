#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContactGenerator.h"
#include "R3D/ParticleEngine/ParticleContactResolver.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <algorithm>

namespace rum
{
	ParticleWorld::ParticleWorld(const unsigned int maxContacts, const unsigned int iterations)
		: m_maxContacts{maxContacts},
		m_calculateIterations{true},
		m_iterations{iterations}
	{
		m_contacts = new ParticleContact[maxContacts];
		m_calculateIterations = iterations == 0;
		m_resolver = std::make_unique<ParticleContactResolver>(iterations);
	}
	
	ParticleWorld::~ParticleWorld()
	{
		delete[] m_contacts;
	}
	
	void ParticleWorld::onBegin()
	{
		for (auto* it : m_particles)
		{
			it->clearAccumulator();
		}
	}
	
	unsigned ParticleWorld::generateContacts()
	{
		auto limit = m_maxContacts;
		auto* nextContact = m_contacts; // erstes Element;
		for (auto& it : m_contactGenerators) 
		{
			const auto used = it->addContact(nextContact, limit);
			limit -= used;
			nextContact += used;
			if(limit <= 0)
			{
				break; // Contacts are missing!
			}
		}
		return m_maxContacts - limit;
	}
	
	void ParticleWorld::reset()
	{
		delete[] m_contacts;

		m_calculateIterations = true;
		m_contacts = new ParticleContact[m_maxContacts];
		m_calculateIterations = (m_iterations == 0);
		m_resolver = std::make_unique<ParticleContactResolver>(m_iterations);
	}

	void ParticleWorld::step(const real timeDelta)
	{
		m_registry.updateForces(timeDelta);
	}

	void ParticleWorld::integrate(const real timeDelta)
	{
		for (auto& p : m_particles) 
		{
			p->integrate(timeDelta);
		}
		runCollisionSolver(timeDelta);
	}
	
	void ParticleWorld::runCollisionSolver(const real timeDelta)
	{
		const auto usedContacts = generateContacts();
		if (usedContacts)
		{
			if (m_calculateIterations) 
			{
				m_resolver->setIterations(usedContacts * 2);
			}
			m_resolver->resolveContacts(m_contacts, usedContacts, timeDelta);
		}
	}
	
	void ParticleWorld::addParticle(Particle* p)
	{
		m_particles.push_back(p);
	}
	
	void ParticleWorld::removeParticle(Particle* p)
	{
		std::remove(m_particles.begin(), m_particles.end(), p);
	}
	
	void ParticleWorld::removeAllParticles()
	{
		m_particles.clear();
	}

	void ParticleWorld::addContactGenerator(ParticleContactGenerator* pcg)
	{
		m_contactGenerators.push_back(pcg);
	}
	
	void ParticleWorld::removeContactGenerator(ParticleContactGenerator* pcg)
	{
		std::remove(m_contactGenerators.begin(), m_contactGenerators.end(), pcg);
	}
	
	rum::ParticleForceRegistry& ParticleWorld::getParticleForceRegistry()
{
		return m_registry;
	}

	void ParticleWorld::removeAllContactGenerators()
	{
		m_contactGenerators.clear();
	}

}