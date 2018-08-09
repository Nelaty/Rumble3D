#pragma once
#include "ForceGenerator.h"
#include "R3D/Common/Precision.h"

#include <glm/glm.hpp>

namespace rum
{
	class RigidBody;

	class AnchoredSpring : public ForceGenerator
	{
	public:
		AnchoredSpring(const glm::vec3& anchor,
					   const glm::vec3& localConnectionPoint,
					   real springConstant,
					   real restLength);

		virtual void UpdateForce(RigidBody* body, real duration) override;

	protected:
		glm::vec3 m_connectionPoint; // in lokalen Koordinaten des Körpers
		glm::vec3 m_anchor; // in Weltkoordinaten
		real m_springConstant; // Federkonstante
		real m_restLength;
	};
}
