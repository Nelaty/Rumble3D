#pragma once
#include "RigidBodyEngineCI.h"
#include "R3D/Common/Common.h"

#include <memory>

namespace r3
{
	class ICollisionResolverAccess;

	class R3D_DECLSPEC DefaultRigidBodyEngineCI : public RigidBodyEngineCI
	{
	public:
		explicit DefaultRigidBodyEngineCI();
		~DefaultRigidBodyEngineCI();

		void onBegin() override;
		void step(real timeDelta) override;
		void integrate(real timeDelta) override;
		void onEnd() override;

		void reset() override;

	private:
		void init();
	};
}
