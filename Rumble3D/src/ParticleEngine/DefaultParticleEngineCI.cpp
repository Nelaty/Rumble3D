#include "R3D/ParticleEngine/DefaultParticleEngineCI.h"
#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContactGenerator.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <cassert>
#include <memory>

namespace r3
{
	DefaultParticleEngineCI::DefaultParticleEngineCI(const unsigned contactsMax,
													 const unsigned iterations,
													 ParticleWorld* particleWorld)
		: ParticleEngineCI(particleWorld),
		m_resolver(iterations),
		m_contactData(contactsMax),
		m_contactsMax(contactsMax),
		m_iterations(iterations)
	{
		reset();
	}

	void DefaultParticleEngineCI::onBegin()
	{
		assert(m_particleWorld != nullptr);
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
		for(int i = 0; i < particles.size(); ++i)
		{
			particles[i]->integrate(timeDelta);
		}

		/*
		// Problem with this: 
		// If someone adds particles in "integrate", all iterators
		// of the "particles"-container will be invalidated
		// -> very confusing crashes
		// \todo check if it should be forbidden to derive from particle
		for (auto& p : particles)
		{
			p->integrate(timeDelta);
		}
		*/
		runCollisionSolver(timeDelta);
	}

	void DefaultParticleEngineCI::onEnd()
	{
		assert(m_particleWorld != nullptr);

		auto& particles = m_particleWorld->getParticles();
		for(auto& it : particles)
		{
			it->clearAccumulator();
		}
		m_contactData.reset();
	}

	void DefaultParticleEngineCI::runCollisionSolver(const real timeDelta)
	{
		generateContacts();
		const auto usedContacts = m_contactData.getEntriesUsed();
		if(m_contactData.getEntriesUsed() != 0)
		{
			if(m_calculateIterations)
			{
				m_resolver.setIterationsMax(usedContacts * 2);
			}
			m_resolver.resolveContacts(m_contactData, timeDelta);
		}
	}

	void DefaultParticleEngineCI::generateContacts()
	{
		const auto& contactRegistry = m_particleWorld->getContactGeneratorRegistry();
		const auto& contactGenerators = contactRegistry.getGenerators();

		for(const auto& it : contactGenerators)
		{
			if(m_contactData.isFull())
			{
				break;
			}

			it->addContact(m_contactData);
		}
	}
	
	void DefaultParticleEngineCI::reset()
	{
		m_contactData.reset();

		m_calculateIterations = (m_iterations == 0);
		m_resolver.setIterationsMax(m_iterations);
	}

	void DefaultParticleEngineCI::setContactsMax(const unsigned contactsMax)
	{
		m_contactsMax = contactsMax;
		m_contactData.init(contactsMax);
	}
}
