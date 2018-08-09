#pragma once
#include "RigidBody.h"

#include <glm/glm.hpp>

namespace rum
{
	class Rigidbody;

	class CollisionPrimitive
	{
	public:
		virtual ~CollisionPrimitive();

		// Berechnet die Transformation:
		void CalculateInternals();
		// Rückgabe der i-ten Spalte der Transformationsmatrix:
		glm::vec3 GetAxis(unsigned index) const;
		const glm::mat4 & GetTransform() const;
		RigidBody * GetBody() const;

	protected:
		explicit CollisionPrimitive();

		// Festkörper, der duch das Objekt repräsentiert wird.
		RigidBody *m_body;
		// Offset gegenüber dem repräsentierten Festkörper.
		glm::mat4 m_offset;
		glm::mat4 m_transform;
	};
}