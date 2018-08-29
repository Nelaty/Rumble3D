#pragma once
#include "ForceGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class RigidBody;

	class R3D_DECLSPEC AnchoredSpring : public ForceGenerator
	{
	public:
		explicit AnchoredSpring(const glm::vec3& anchor,
								const glm::vec3& localConnectionPoint,
								real springConstant,
								real restLength);
		~AnchoredSpring();

		void updateForce(RigidBody* body, real duration) override;

	protected:
		glm::vec3 m_connectionPoint; // in lokalen Koordinaten des Körpers
		glm::vec3 m_anchor; // in Weltkoordinaten
		real m_springConstant; // Federkonstante
		real m_restLength;
	};
}
