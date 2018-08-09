#include "R3D/ParticleEngine/ParticleWorld.h"
#include "R3D/ParticleEngine/Particle.h"
#include "R3D/ParticleEngine/ParticleContactGenerator.h"
#include "R3D/ParticleEngine/ParticleContactResolver.h"
#include "R3D/ParticleEngine/ParticleContact.h"

#include <algorithm>

namespace rum
{
	ParticleWorld::ParticleWorld(unsigned int maxContacts, unsigned int iterations)
		: m_maxContacts(maxContacts),
		m_iterations(iterations),
		m_calculateIterations{true}
	{
		m_contacts = new ParticleContact[maxContacts];
		m_calculateIterations = (iterations == 0);
		m_resolver = std::make_unique<ParticleContactResolver>(iterations);
	}
	
	ParticleWorld::~ParticleWorld()
	{
		delete[] m_contacts;
	}
	
	void ParticleWorld::OnBegin()
	{
		for (auto* it : m_particles)
		{
			it->ClearAccumulator();
		}
	}
	
	unsigned ParticleWorld::GenerateContacts()
	{
		unsigned int limit = m_maxContacts;
		ParticleContact * nextContact = m_contacts; // erstes Element;
		for (auto& it : m_contactGenerators) 
		{
			unsigned int used = it->AddContact(nextContact, limit);
			limit -= used;
			nextContact += used;
			if(limit <= 0)
			{
				break; // Contacts are missing!
			}
		}
		return m_maxContacts - limit;
	}
	
	void ParticleWorld::Reset()
	{
		delete[] m_contacts;

		m_calculateIterations = true;
		m_contacts = new ParticleContact[m_maxContacts];
		m_calculateIterations = (m_iterations == 0);
		m_resolver = std::make_unique<ParticleContactResolver>(m_iterations);
	}

	void ParticleWorld::Step(const real timeDelta)
	{
		m_registry.UpdateForces(timeDelta);
	}

	void ParticleWorld::Integrate(real timeDelta)
	{
		for (auto& p : m_particles) 
		{
			p->Integrate(timeDelta);
		}

		RunCollisionSolver(timeDelta);
	}
	
	void ParticleWorld::RunCollisionSolver(real timeDelta)
	{
		unsigned int usedContacts = GenerateContacts();
		if (usedContacts)
		{
			if (m_calculateIterations) 
			{
				m_resolver->SetIterations(usedContacts * 2);
			}
			m_resolver->ResolveContacts(m_contacts, usedContacts, timeDelta);
		}
	}
	
	void ParticleWorld::AddParticle(Particle* p)
	{
		m_particles.push_back(p);
	}
	
	void ParticleWorld::RemoveParticle(Particle* p)
	{
		std::remove(m_particles.begin(), m_particles.end(), p);
	}
	
	void ParticleWorld::RemoveAllParticles()
	{
		m_particles.clear();
	}

	void ParticleWorld::AddContactGenerator(ParticleContactGenerator* pcg)
	{
		m_contactGenerators.push_back(pcg);
	}
	
	void ParticleWorld::RemoveContactGenerator(ParticleContactGenerator* pcg)
	{
		std::remove(m_contactGenerators.begin(), m_contactGenerators.end(), pcg);
	}
	
	rum::ParticleForceRegistry& ParticleWorld::GetParticleForceRegistry()
{
		return m_registry;
	}

	void ParticleWorld::RemoveAllContactGenerators()
	{
		m_contactGenerators.clear();
	}

}