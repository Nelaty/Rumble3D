#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	/**
	 * \brief Interface used by physics modules to accomplish their
	 * tasks.
	 */
	class R3D_DECLSPEC IComputationInterface
	{
	public:
		virtual ~IComputationInterface();

		/**
		 * \brief Called at the start of a physics step.
		 */
		virtual void onBegin() = 0;
		/**
		 * \brief Used to calculate changes.
		 * \param timeDelta The time step of the physics step.
		 */
		virtual void step(real timeDelta) = 0;
		/**
		 * \brief Used to apply changes.
		 * \param timeDelta The time step of the physics step.
		 */
		virtual void integrate(real timeDelta) = 0;
		/**
		 * \brief Called at the end of a physics step.
		 */
		virtual void onEnd() = 0;

		/**
		 * \brief Resets a computation interface to its start state.
		 */
		virtual void reset() = 0;

	protected:
		explicit IComputationInterface();
	};
}