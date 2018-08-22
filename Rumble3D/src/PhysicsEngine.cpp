#include "R3D/PhysicsEngine.h"
#include "R3D/PhysicsEngineModule.h"

#include <algorithm>

namespace rum
{
	PhysicsEngine::PhysicsEngine()
	= default;

	PhysicsEngine::~PhysicsEngine()
	= default;

	void PhysicsEngine::update(const real timeDelta)
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

	rum::PhysicsEngineModule* PhysicsEngine::registerModule(const std::string& key, PhysicsEngineModule* module)
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
				it.second->onBegin();
			}	
		}
	}

	void PhysicsEngine::onEnd()
	{
		for(auto& it : m_modules)
		{
			if(it.second->isEnabled())
			{
				it.second->onEnd();
			}
		}
	}

	void PhysicsEngine::step(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it.second->isEnabled())
			{
				it.second->step(timeDelta);
			}
		}
	}

	void PhysicsEngine::integrate(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it.second->isEnabled())
			{
				it.second->integrate(timeDelta);
			}
		}
	}

}
