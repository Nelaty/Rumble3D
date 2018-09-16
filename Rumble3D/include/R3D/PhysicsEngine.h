#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <map>
#include <string>

namespace r3
{
	class PhysicsEngineModule;

	/**
	 * \brief The PhysicsEngine is the main component of this library and consists
	 * of multiple PhysicsEngineModule.
	 */
	class R3D_DECLSPEC PhysicsEngine
	{
	public:
		explicit PhysicsEngine();
		~PhysicsEngine();

		/** 
		 * \brief Update all enabled physic modules. 
		 */
		void tick(real timeDelta);

		/** 
		 * \brief Try to find an existing module.
		 * \return The found module or nullptr if the module doesn't exist.
		 */
		PhysicsEngineModule* findModule(const std::string& key) const;

		/**
		 * Check if a module with the given key is already registered.
		 * \return True if module is registered.
		 */
		bool isModuleRegistered(const std::string& key) const;

		/** 
		 * \brief Register a new physics module with a given key. Fails, when a
		 * module with the same key is already registered.
		 * \return The registered module or an existing module with the same key.
		 */
		PhysicsEngineModule* registerModule(PhysicsEngineModule* module, const std::string& key);

		/**
		 * \brief Unregister an existing physics module. 
		 * \return The unregistered module or nullptr if the module doesn't exist.
		 */
		PhysicsEngineModule* unregisterModule(const std::string& key);		

		/**
		 * \brief Check if the simulation is currently paused.
		 * \return True if the simulation is paused, false otherwise.
		 */
		bool isPaused() const;
		/**
		 * \brief Pause the physic simulation.
		 */
		void pause();
		/**
		 * \brief Resume the physic simulation, if it was paused.
		 */
		void resume();

	private:
		/** 
		 * \brief Calls onBegin function on every module. 
		 */
		void onBegin();
		/** 
		 * \brief Calls onEnd function on every module. 
		 */
		void onEnd();
		/** 
		 * \brief Calls step function on every module. 
		 */
		void step(real timeDelta);
		/** 
		 * \brief Calls integrate function on every module. 
		 */
		void integrate(real timeDelta);

		bool m_paused;
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