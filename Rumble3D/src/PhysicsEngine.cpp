#include "R3D/PhysicsEngine.h"
#include "R3D/PhysicsEngineModule.h"
#include "R3D/IComputationInterface.h"

namespace rum
{
	PhysicsEngine::PhysicsEngine()
	= default;

	PhysicsEngine::~PhysicsEngine()
	= default;

	void PhysicsEngine::tick(const real timeDelta)
	{
		onBegin();
		step(timeDelta);
		integrate(timeDelta);
		onEnd();
	}

	rum::PhysicsEngineModule* PhysicsEngine::findModule(const std::string& key) const
	{
		const auto foundModule = m_modules.find(key);
		return foundModule->second;
	}

	bool PhysicsEngine::isModuleRegistered(const std::string& key) const
	{
		return findModule(key) != nullptr;
	}

	rum::PhysicsEngineModule* PhysicsEngine::registerModule(PhysicsEngineModule* module, const std::string& key)
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

	rum::PhysicsEngineModule* PhysicsEngine::unregisterModule(const std::string& key)
	{
		const auto removedModule = m_modules.find(key);
		if(removedModule == m_modules.end())
		{
			return nullptr;
		}
		auto module = removedModule->second;
		m_modules.erase(removedModule);
		return module;
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
