#pragma once
#include "R3D/Common/Common.h"

namespace rum
{
	class IComputationInterface;

	/**
	 * Abstract class for physic engine modules.
	 */
	class R3D_DECLSPEC PhysicsEngineModule
	{
	public:
		virtual ~PhysicsEngineModule();

		/**
		 * Get the computation interface of this module.
		 */
		virtual IComputationInterface* getComputationInterface() const = 0;

		/**
		 * Enable or disable this module.
		 */
		void enable(bool enabled);
		/**
		 * Check if this module is currently enabled.
		 * \return true if currently enabled.
		 */
		bool isEnabled() const;

	protected:
		explicit PhysicsEngineModule();

		bool m_enabled;
	};
}