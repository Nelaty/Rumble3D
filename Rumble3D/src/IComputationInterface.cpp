#include "R3D/IComputationInterface.h"

namespace rum
{
	IComputationInterface::~IComputationInterface()
	= default;

	void IComputationInterface::onBegin()
	{
	}

	void IComputationInterface::step(real timeDelta)
	{
	}

	void IComputationInterface::integrate(real timeDelta)
	{
	}

	void IComputationInterface::onEnd()
	{
	}

	void IComputationInterface::reset()
	{
	}

	IComputationInterface::IComputationInterface()
	= default;
}
