#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/PhysicsMaterial.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionMask.h"
#include "R3D/RigidBodyEngine/CollisionPrimitive.h"

#include <glm/glm.hpp>


namespace r3
{
	/**
	 * \brief Bundles construction information about a rigid body.
	 */
	struct R3D_DECLSPEC RigidBodyDef
	{
		PhysicsMaterial m_physicsMaterial{};
		CollisionPrimitive* m_collisionPrimitive{};
		CollisionMask m_collisionMask{};

		void setMass(real mass);
		void setMassInfinite();
		real m_inverseMass{0.0f};
		
		real m_linearDamping{0.95f};
		real m_angularDamping{0.99f};

		glm::vec3 m_velocity{0.0f};
		glm::vec3 m_acceleration{0.0f};
		glm::vec3 m_lastFrameAcceleration{0.0f};
		glm::vec3 m_rotation{0.0f};

		glm::mat4 m_transformationMatrix{1.0f};
		glm::mat3 m_inverseInertiaTensor{1.0f};
		glm::mat3 m_inverseInertiaTensorWorld{1.0f};

		/* Accumulators */
		glm::vec3 m_forceAccumulated{0.0f};
		glm::vec3 m_torqueAccumulated{0.0f};
		bool m_awake{true};
	};
}
