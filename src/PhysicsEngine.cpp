#include "R3D/PhysicsEngine.h"
#include "R3D/PhysicsEngineModule.h"
#include "R3D/IComputationInterface.h"

namespace r3
{
	PhysicsEngine::PhysicsEngine()
	= default;

	PhysicsEngine::~PhysicsEngine()
	= default;

	void PhysicsEngine::tick(const real timeDelta)
	{
		if(m_paused)
		{
			return;
		}

		onBegin();
		step(timeDelta);
		integrate(timeDelta);
		onEnd();
	}

	r3::PhysicsEngineModule* PhysicsEngine::findModule(const std::string& key) const
	{
		const auto foundModule = m_modules.find(key);
		if(foundModule == m_modules.end())
		{
			return nullptr;
		}
		return foundModule->second;
	}

	bool PhysicsEngine::isModuleRegistered(const std::string& key) const
	{
		return findModule(key) != nullptr;
	}

	r3::PhysicsEngineModule* PhysicsEngine::registerModule(PhysicsEngineModule* module, const std::string& key)
	{
		const auto foundModule = findModule(key);
		if(foundModule)
		{
			return foundModule;
		}
		auto entry = std::make_pair(key, module);
		m_modules.insert(entry);
		return module;
	}

	r3::PhysicsEngineModule* PhysicsEngine::unregisterModule(const std::string& key)
	{
		const auto removedModule = m_modules.find(key);
		if(removedModule == m_modules.end())
		{
			return nullptr;
		}
		const auto module = removedModule->second;
		m_modules.erase(removedModule);
		return module;
	}

	bool PhysicsEngine::isPaused() const
	{
		return m_paused;
	}

	void PhysicsEngine::pause()
	{
		m_paused = true;
	}

	void PhysicsEngine::resume()
	{
		m_paused = false;
	}

	void PhysicsEngine::onBegin()
	{
		for(auto& it : m_modules)
		{
			if(it.second->isEnabled())
			{
				auto compInterface = it.second->getComputationInterface();
				compInterface->onBegin();
			}	
		}
	}

	void PhysicsEngine::onEnd()
	{
		for(auto& it : m_modules)
		{
			if(it.second->isEnabled())
			{
				auto compInterface = it.second->getComputationInterface();
				compInterface->onEnd();
			}
		}
	}

	void PhysicsEngine::step(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it.second->isEnabled())
			{
				auto compInterface = it.second->getComputationInterface();
				compInterface->step(timeDelta);
			}
		}
	}

	void PhysicsEngine::integrate(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it.second->isEnabled())
			{
				auto compInterface = it.second->getComputationInterface();
				compInterface->integrate(timeDelta);
			}
		}
	}

}
