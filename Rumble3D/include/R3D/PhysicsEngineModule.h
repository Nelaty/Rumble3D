#pragma once
#include "R3D/Common/Precision.h"

#include <memory>

namespace rum
{

	/**
	 * Abstract class for physic engine modules.
	 */
	class PhysicsEngineModule
	{
	public:
		virtual ~PhysicsEngineModule();

		virtual void onBegin();
		virtual void onEnd();

		/**
		*  Calculate changes in the physics engine and accumulate
		*  them in buffers.
		*  Will not apply those changes yet.
		*/
		virtual void step(real timeDelta) = 0;
		/**
		*  Apply the changes as a result of the simulation.
		*/
		virtual void integrate(real timeDelta) = 0;

		/**
		* Reset the physics engine module to its initial state
		*/
		virtual void reset() = 0;

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