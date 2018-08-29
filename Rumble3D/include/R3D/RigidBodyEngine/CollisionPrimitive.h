#pragma once
#include "R3D/Common/Common.h"

#include <glm/glm.hpp>

namespace rum
{
	class RigidBody;
	class INarrowPhaseFilter;

	class CollisionBox;
	class CollisionSphere;

	class R3D_DECLSPEC CollisionPrimitive
	{
	public:
		virtual ~CollisionPrimitive();

		virtual void generateContact(INarrowPhaseFilter* filter,
									 CollisionPrimitive* other) = 0;

		void generateContact(INarrowPhaseFilter* filter,
							 CollisionBox* other);

		void generateContact(INarrowPhaseFilter* filter,
							 CollisionSphere* other);		

		// Berechnet die Transformation:
		void calculateInternals();
		// Rückgabe der i-ten Spalte der Transformationsmatrix:
		glm::vec3 getAxis(unsigned index) const;
		const glm::mat4 & getTransform() const;
		RigidBody* getBody() const;

	protected:
		explicit CollisionPrimitive();

		// Festkörper, der duch das Objekt repräsentiert wird.
		RigidBody* m_body{};
		// Offset gegenüber dem repräsentierten Festkörper.
		glm::mat4 m_offset;
		glm::mat4 m_transform;
	};
}