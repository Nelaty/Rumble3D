#include "R3D/RigidBodyEngine/ComputationInterfaceFactory.h"

#include "R3D/ParticleEngine/DefaultParticleEngineCI.h"
#include "R3D/RigidBodyEngine/DefaultRigidBodyEngineCI.h"

#include <utility>

namespace r3
{
	std::unique_ptr<ParticleEngineCI> ComputationInterfaceFactory::getParticleEngineCI()
	{
		auto ci = std::make_unique<DefaultParticleEngineCI>(1000);
		return std::move(ci);
	}

	std::unique_ptr<RigidBodyEngineCI> ComputationInterfaceFactory::getRigidBodyEngineCI()
	{
		auto ci = std::make_unique<DefaultRigidBodyEngineCI>();
		return std::move(ci);
	}
}
