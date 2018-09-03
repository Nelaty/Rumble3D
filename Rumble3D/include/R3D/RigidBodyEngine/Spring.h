#pragma once
#include "R3D/RigidBodyEngine/ForceGenerator.h"

#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace r3
{
	class RigidBody;

	class R3D_DECLSPEC Spring : public ForceGenerator
	{
	public:
		Spring(const glm::vec3& localConnectionPoint,
			   RigidBody* other,
			   const glm::vec3& otherConnectionPoint,
			   real springConstant,
			   real restLength);

		void updateForce(RigidBody* body, real duration) override;

	protected:
		glm::vec3 m_connectionPoint; // in lokalen Koordinaten des Körpers
		glm::vec3 m_otherConnectionPoint; // in lokalen Koordinaten des anderen Körpers
		RigidBody* m_other; // Der körper am anderen Ende der Feder.
		real m_springConstant; // Federkonstante
		real m_restLength;
	};
}