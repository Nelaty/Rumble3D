#pragma once
#include <memory>

namespace r3
{
	class ParticleEngineCI;
	class RigidBodyEngineCI;

	class ServiceLocatorComputationInterface
	{
	public:
		static std::unique_ptr<ParticleEngineCI> getParticleEngineCI();
		static std::unique_ptr<RigidBodyEngineCI> getRigidBodyEngineCI();

	private:
		explicit ServiceLocatorComputationInterface();
		~ServiceLocatorComputationInterface();
	};
}