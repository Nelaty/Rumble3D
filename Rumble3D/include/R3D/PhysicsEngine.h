#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <vector>
#include <string>
#include <memory>

namespace r3
{
	class PhysicsEngineModule;

	/**
	 * \brief The PhysicsEngine is the main component of this library and consists
	 * of multiple PhysicsEngineModule.
	 */
	class R3D_EXPORT PhysicsEngine
	{
	public:
		explicit PhysicsEngine() = default;
		~PhysicsEngine() = default;

		/** 
		 * \brief Update all enabled physic modules. 
		 */
		void tick(real timeDelta);

		/**
		 * Check if a module with the given key is already registered.
		 * \return True if module is registered.
		 */
		bool isModuleRegistered(std::string_view key) const;
        /**
         * Check if a module is already registered.
         * \return True if module is registered.
         */
        bool isModuleRegistered(PhysicsEngineModule* module) const;
        /**
         * Check if a module is already registered.
         * \return True if module is registered.
         */
        bool isModuleRegistered(const std::shared_ptr<PhysicsEngineModule>& module) const;
        /**
		 * Search for a module by its name.
		 * @param name The name of the module.
		 * @return Returns the first occurence of a module with the given name or nullptr if none was found.
		 */
        std::shared_ptr<PhysicsEngineModule> findModule(std::string_view name) const;
        /**
         * Get all registered modules.
         * @return All registered modules.
         */
        std::vector<std::shared_ptr<PhysicsEngineModule>>& getModules();
        /**
         * Register a new module.
         * @param module The module to register.
         */
		void registerModule(const std::shared_ptr<PhysicsEngineModule>& module);
		/**
		 * Unregister a given module.
		 * @param module The module to unregister.
		 * @return Returns true if the module was found, false otherwise.
		 */
		void unregisterModule(const std::shared_ptr<PhysicsEngineModule>& module);
		/**
		 * Unregister the first module with the given name.
		 * @param name The name of the module to unregister.
		 * @return Returns true if the module was found, false otherwise.
		 */
        void unregisterModule(std::string_view name);

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

		bool m_paused{false};
		std::vector<std::shared_ptr<PhysicsEngineModule>> m_modules;
	};
}