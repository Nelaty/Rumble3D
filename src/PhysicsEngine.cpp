#include "R3D/PhysicsEngine.h"
#include "R3D/PhysicsEngineModule.h"
#include "R3D/IComputationInterface.h"

#include <algorithm>

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

    bool PhysicsEngine::isModuleRegistered(std::string_view key) const
    {
        auto found = std::find_if(m_modules.begin(), m_modules.end(), [&]
        (const std::shared_ptr<PhysicsEngineModule>& module)
        {
           return module->getName() == key;
        });

        return found != m_modules.end();
    }

    std::shared_ptr<PhysicsEngineModule> PhysicsEngine::findModule(std::string_view name) const
    {
	    auto found = std::find_if(m_modules.begin(), m_modules.end(), [&]
            (const std::shared_ptr<PhysicsEngineModule& module)
        {
	       return module->getName() == key;
        });

	    return found != m_modules.end() ? *found : nullptr;
    }

    void PhysicsEngine::registerModule(const std::shared_ptr<PhysicsEngineModule>& module)
    {
        m_modules.emplace_back(module);
    }

    bool PhysicsEngine::unregisterModule(const std::shared_ptr<PhysicsEngineModule>& module)
    {
        auto removed = std::remove(m_modules.begin(), m_modules.end(), module);
        if(removed != m_modules.end())
        {
            m_modules.erase(removed);
            return true;
        }
        return false;
    }
    bool PhysicsEngine::unregisterModule(std::string_view name)
    {
	    auto removed = std::remove_if(m_modules.begin(), m_modules.end(), [&]
            (const std::shared_potr<PhysicsEngineModule>& module)
        {
	        return module->getName() == name;
        });

	    if(removed != m_modules.end())
	    {
            m_modules.erase(removed);
            return true;
        }
        return false;
    }
}
