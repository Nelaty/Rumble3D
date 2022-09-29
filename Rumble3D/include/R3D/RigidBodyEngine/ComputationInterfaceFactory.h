#pragma once
#include "R3D/Common/Common.h"

#include <memory>

namespace r3
{
	class ParticleEngineCI;
	class RigidBodyEngineCI;

	/**
	 * \brief Generate default implementations of various computation
	 * interfaces.
	 */
	class R3D_EXPORT ComputationInterfaceFactory
	{
	public:
		/**
		 * \brief Generate a default computation interface
		 * implementation for a particle engine.
		 * \return The new computation interface.
		 */
		static std::unique_ptr<ParticleEngineCI> getParticleEngineCI();
		/**
		 * \brief Generate a default computation interface
		 * implementation for a rigid body engine.
		 * \return The new computation interface.
		 */
		static std::unique_ptr<RigidBodyEngineCI> getRigidBodyEngineCI();

	private:
		explicit ComputationInterfaceFactory() = default;
		~ComputationInterfaceFactory() = default;
	};
}