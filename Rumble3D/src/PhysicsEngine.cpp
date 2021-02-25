#include "R3D/PhysicsEngine.h"
#include "R3D/PhysicsEngineModule.h"
#include "R3D/IComputationInterface.h"

#include <algorithm>

namespace r3
{
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
			if(it->isEnabled())
			{
				auto compInterface = it->getComputationInterface();
				compInterface->onBegin();
			}	
		}
	}

	void PhysicsEngine::onEnd()
	{
		for(auto& it : m_modules)
        {
			if(it->isEnabled())
			{
				auto compInterface = it->getComputationInterface();
				compInterface->onEnd();
			}
		}
	}

	void PhysicsEngine::step(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it->isEnabled())
			{
				auto compInterface = it->getComputationInterface();
				compInterface->step(timeDelta);
			}
		}
	}

	void PhysicsEngine::integrate(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it->isEnabled())
			{
				auto compInterface = it->getComputationInterface();
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
            (const std::shared_ptr<PhysicsEngineModule>& module)
        {
	       return module->getName() == name.data();
        });

	    return found != m_modules.end() ? *found : nullptr;
    }

    void PhysicsEngine::registerModule(const std::shared_ptr<PhysicsEngineModule>& module)
    {
        m_modules.emplace_back(module);
    }

    void PhysicsEngine::unregisterModule(const std::shared_ptr<PhysicsEngineModule>& module)
    {
	    m_modules.erase(
	        std::remove(m_modules.begin(),
	            m_modules.end(),
	            module),
            m_modules.end());
    }

    void PhysicsEngine::unregisterModule(std::string_view name)
    {
        m_modules.erase(
            std::remove_if(m_modules.begin(),
                        m_modules.end(),
                           [&]
                               (const std::shared_ptr<PhysicsEngineModule>& module)
                           {
                               return module->getName() == name;
                           }),
            m_modules.end());
    }

    std::vector<std::shared_ptr<PhysicsEngineModule>>& PhysicsEngine::getModules()
    {
        return m_modules;
    }

    bool PhysicsEngine::isModuleRegistered(PhysicsEngineModule *module) const
    {
        return std::find_if(m_modules.begin(), m_modules.end(), [&](auto it)
        {
            return it.get() == module;
        }) != m_modules.end();
    }

    bool PhysicsEngine::isModuleRegistered(const std::shared_ptr<PhysicsEngineModule>& module) const
    {
        return std::find(m_modules.begin(), m_modules.end(), module) != m_modules.end();
    }
}
