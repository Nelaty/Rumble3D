#pragma once
#include "RigidBodyEngineCI.h"

#include "R3D/RigidBodyEngine/CollisionDetection/CollisionDetector.h"

#include <memory>

namespace r3
{
	class CollisionResolver;

	class DefaultRigidBodyEngineCI : public RigidBodyEngineCI
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

		CollisionDetector m_collisionDetector;
		std::unique_ptr<CollisionResolver> m_collisionResolver;
	};
}
