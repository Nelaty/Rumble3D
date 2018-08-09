#pragma once
#include "R3D/Common/Precision.h"

#include <string>
#include <map>

namespace rum
{
	class PhysicsEngineModule;

	/**
	 * The PhysicsEngine is the main component of this library and consists
	 * of multiple PhysicsEngineModule.
	 */
	class PhysicsEngine
	{
	public:
		explicit PhysicsEngine();
		~PhysicsEngine();

		/** 
		 * Update physic modules. 
		 */
		void Update(const real timeDelta);

		/** 
		 * Try to find an existing module.
		 * \return The found module or nullptr if the module doesn't exist.
		 */
		PhysicsEngineModule* FindModule(const std::string& key) const;

		/**
		 * Check if a module with the given key is already registered.
		 * \return True if module is registered.
		 */
		bool IsModuleRegistered(const std::string& key) const;

		/** 
		 * Register a new physics module with a given key. Fails, when a
		 * module with the same key is already registered.
		 * \return The registered module or an existing module with the same key.
		 */
		PhysicsEngineModule* RegisterModule(const std::string& key, PhysicsEngineModule* module);

		/** 
		 * Unregister an existing physics module. 
		 * \return The unregistered module or nullptr if the module doesn't exist.
		 */
		PhysicsEngineModule* UnregisterModule(const std::string& key);		

	private:
		/** 
		 * Calls OnBegin function on every module. 
		 */
		void OnBegin();
		/** 
		 * Calls OnEnd function on every module. 
		 */
		void OnEnd();
		/** 
		 * Calls Step function on every module. 
		 */
		void Step(const real timeDelta);
		/** 
		 * Calls Integrate function on every module. 
		 */
		void Integrate(const real timeDelta);

		std::map<std::string, PhysicsEngineModule*> m_modules;
	};

	/// \todo REMOVE TestClass
	class TestClass
	{
	public:
		int Test()
		{
			return 3;
		}
	};
}