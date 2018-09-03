#include "R3D/RigidBodyEngine/CollisionPrimitive.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

#include "R3D/RigidBodyEngine/CollisionDetection/INarrowPhaseFilter.h"

#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

namespace r3
{
	CollisionPrimitive::~CollisionPrimitive()
	= default;

	void CollisionPrimitive::generateContact(INarrowPhaseFilter* filter,
											 CollisionBox* other)
	{
		
	}

	void CollisionPrimitive::generateContact(INarrowPhaseFilter* filter, 
											 CollisionSphere* other)
	{
		
	}

	void CollisionPrimitive::calculateInternals()
	{
		m_transform = m_body->getTransformationMatrix() * m_offset;
	}

	glm::vec3 CollisionPrimitive::getAxis(unsigned index) const
	{
		return m_transform[index];
	}

	const glm::mat4& CollisionPrimitive::getTransform() const
	{
		return m_transform;
	}

	RigidBody* CollisionPrimitive::getBody() const
	{
		return m_body;
	}

	CollisionPrimitive::CollisionPrimitive()
	= default;
}
