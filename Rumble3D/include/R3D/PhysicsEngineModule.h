#pragma once
#include <R3D/Common/Common.h>

#include <string>

namespace r3
{
	class IComputationInterface;

	/**
	 * \brief Abstract class for physic engine modules.
	 */
	class R3D_DECLSPEC PhysicsEngineModule
	{
	public:
		virtual ~PhysicsEngineModule() = default;

		/**
		 * \brief Get the computation interface of this module.
		 * \return The computation interface.
		 */
		virtual IComputationInterface* getComputationInterface() const = 0;

		/**
		 * \brief Enable or disable this module.
		 * \param enabled True will enable it, false disable it.
		 */
		void enable(bool enabled);
		/**
		 * \brief Check if this module is currently enabled.
		 * \return True if enabled, false otherwise.
		 */
		bool isEnabled() const;

        /** Set the name of this module */
		void setName(std::string_view name);
		/** Get the name of this module */
		std::string_view getName() const;

	protected:
		explicit PhysicsEngineModule(std::string_view name = "");

		std::string m_name;
		bool m_enabled;
	};
}