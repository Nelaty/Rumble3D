#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <map>
#include <string>

namespace rum
{
	class PhysicsEngineModule;

	/**
	 * The PhysicsEngine is the main component of this library and consists
	 * of multiple PhysicsEngineModule.
	 */
	class R3D_DECLSPEC PhysicsEngine
	{
	public:
		explicit PhysicsEngine();
		~PhysicsEngine();

		/** 
		 * Update all enabled physic modules. 
		 */
		void tick(real timeDelta);

		/** 
		 * Try to find an existing module.
		 * \return The found module or nullptr if the module doesn't exist.
		 */
		PhysicsEngineModule* findModule(const std::string& key) const;

		/**
		 * Check if a module with the given key is already registered.
		 * \return True if module is registered.
		 */
		bool isModuleRegistered(const std::string& key) const;

		/** 
		 * Register a new physics module with a given key. Fails, when a
		 * module with the same key is already registered.
		 * \return The registered module or an existing module with the same key.
		 */
		PhysicsEngineModule* registerModule(PhysicsEngineModule* module, const std::string& key);

		/**
		 * Unregister an existing physics module. 
		 * \return The unregistered module or nullptr if the module doesn't exist.
		 */
		PhysicsEngineModule* unregisterModule(const std::string& key);		

	private:
		/** 
		 * Calls onBegin function on every module. 
		 */
		void onBegin();
		/** 
		 * Calls onEnd function on every module. 
		 */
		void onEnd();
		/** 
		 * Calls step function on every module. 
		 */
		void step(real timeDelta);
		/** 
		 * Calls integrate function on every module. 
		 */
		void integrate(real timeDelta);

		std::map<std::string, PhysicsEngineModule*> m_modules;
	};

	/// \todo REMOVE TestClass
	class TestClass
	{
	public:
		static int test()
		{
			return 3;
		}
	};
}