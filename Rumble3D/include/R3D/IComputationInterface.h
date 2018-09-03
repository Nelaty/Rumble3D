#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class R3D_DECLSPEC IComputationInterface
	{
	public:
		virtual ~IComputationInterface();

		virtual void onBegin() = 0;
		virtual void step(real timeDelta) = 0;
		virtual void integrate(real timeDelta) = 0;
		virtual void onEnd() = 0;

		virtual void reset() = 0;

	protected:
		explicit IComputationInterface();
	};
}