#include "R3D/PhysicsEngine.h"
#include "R3D/PhysicsEngineModule.h"

#include <algorithm>

namespace rum
{
	PhysicsEngine::PhysicsEngine()
	{
	}

	PhysicsEngine::~PhysicsEngine()
	{
	}

	void PhysicsEngine::Update(const real timeDelta)
	{
		OnBegin();
		Step(timeDelta);
		Integrate(timeDelta);
		OnEnd();
	}

	rum::PhysicsEngineModule* PhysicsEngine::FindModule(const std::string& key) const
	{
		auto foundModule = m_modules.find(key);
		return foundModule->second;
	}

	bool PhysicsEngine::IsModuleRegistered(const std::string& key) const
	{
		return FindModule(key) != nullptr;
	}

	rum::PhysicsEngineModule* PhysicsEngine::RegisterModule(const std::string& key, PhysicsEngineModule* module)
	{
		auto foundModule = FindModule(key);
		if(foundModule)
		{
			return foundModule;
		}
		else
		{
			auto entry = std::make_pair(key, module);
			m_modules.insert(entry);
			return module;
		}
	}

	rum::PhysicsEngineModule* PhysicsEngine::UnregisterModule(const std::string& key)
	{
		auto removedModule = m_modules.find(key);
		if(removedModule == m_modules.end())
		{
			return nullptr;
		}
		else
		{
			auto module = removedModule->second;
			m_modules.erase(removedModule);
			return module;
		}
	}

	void PhysicsEngine::OnBegin()
	{
		for(auto& it : m_modules)
		{
			if(it.second->IsEnabled())
			{
				it.second->OnBegin();
			}	
		}
	}

	void PhysicsEngine::OnEnd()
	{
		for(auto& it : m_modules)
		{
			if(it.second->IsEnabled())
			{
				it.second->OnEnd();
			}
		}
	}

	void PhysicsEngine::Step(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it.second->IsEnabled())
			{
				it.second->Step(timeDelta);
			}
		}
	}

	void PhysicsEngine::Integrate(const real timeDelta)
	{
		for(auto& it : m_modules)
		{
			if(it.second->IsEnabled())
			{
				it.second->Integrate(timeDelta);
			}
		}
	}

}
