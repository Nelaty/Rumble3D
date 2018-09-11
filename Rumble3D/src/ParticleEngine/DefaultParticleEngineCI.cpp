#include "R3D/ParticleEngine/DefaultParticleEngineCI.h"
#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/ParticleEngine/Particle.h"

#include "R3D/ParticleEngine/ParticleContactGenerator.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <cassert>
#include <memory>

namespace r3
{
	DefaultParticleEngineCI::DefaultParticleEngineCI(const unsigned maxContacts, 
																 const unsigned iterations,
																 ParticleWorld* particleWorld)
		: ParticleEngineCI(particleWorld),
		m_resolver{iterations},
		m_maxContacts{maxContacts},
		m_calculateIterations{true},
		m_iterations{iterations}
	{
		m_contacts = new ParticleContact[m_maxContacts];
		m_calculateIterations = iterations == 0;
	}

	DefaultParticleEngineCI::~DefaultParticleEngineCI()
	= default;

	void DefaultParticleEngineCI::onBegin()
	{
		assert(m_particleWorld != nullptr);

		auto& particles = m_particleWorld->getParticles();
		for(auto& it : particles)
		{
			it->clearAccumulator();
		}
	}

	void DefaultParticleEngineCI::step(const real timeDelta)
	{
		assert(m_particleWorld != nullptr);

		auto& registry = m_particleWorld->getParticleForceRegistry();
		registry.updateForces(timeDelta);
	}

	void DefaultParticleEngineCI::integrate(const real timeDelta)
	{
		assert(m_particleWorld != nullptr);

		auto& particles = m_particleWorld->getParticles();
		for (auto& p : particles)
		{
			p->integrate(timeDelta);
		}
		runCollisionSolver(timeDelta);
	}

	void DefaultParticleEngineCI::onEnd()
	{
		assert(m_particleWorld != nullptr);
	}

	void DefaultParticleEngineCI::runCollisionSolver(const real timeDelta)
	{
		const auto usedContacts = generateContacts();
		if(usedContacts)
		{
			if(m_calculateIterations)
			{
				m_resolver.setIterations(usedContacts * 2);
			}
			
			m_resolver.resolveContacts(m_contacts, usedContacts, timeDelta);
		}
	}

	unsigned DefaultParticleEngineCI::generateContacts() const
	{
		auto contactRegistry = m_particleWorld->getContactGeneratorRegistry();
		auto contactGenerators = contactRegistry.getGenerators();

		auto limit = m_maxContacts;
		auto* nextContact = m_contacts; // erstes Element;
		for (auto& it : contactGenerators)
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
	
	void DefaultParticleEngineCI::reset()
	{
		delete[] m_contacts;
		m_contacts = new ParticleContact[m_maxContacts];

		m_calculateIterations = true;
		m_calculateIterations = (m_iterations == 0);
		m_resolver = ParticleContactResolver(m_iterations);
	}
}
