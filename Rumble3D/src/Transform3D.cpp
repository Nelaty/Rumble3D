#include "R3D/Transform3D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace r3
{
	Transform3D::Transform3D(const glm::vec3& position,
							 const glm::mat3& rotation)
		: m_rotation{rotation},
		m_position{position}
	{
	}

	Transform3D::~Transform3D()
	= default;

	void Transform3D::setPosition(const glm::vec3& position)
	{
		m_position = position;
	}

	void Transform3D::setPosition(const real x, const real y, const real z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}

	const glm::vec3& Transform3D::getPosition() const
	{
		return m_position;
	}

	void Transform3D::translate(const glm::vec3& delta)
	{
		m_position += delta;
	}

	void Transform3D::rotate(const glm::quat& rot)
	{
		m_rotation = m_rotation * glm::toMat3(rot);
	}

	void Transform3D::setRotation(const float w, const float x, const float y, const float z)
	{
		setRotation(glm::quat(w, x, y, z));
	}

	void Transform3D::setRotation(const glm::quat& orientation)
	{
		m_rotation = glm::toMat3(orientation);
	}

	const glm::mat3& Transform3D::getRotation() const
	{
		return m_rotation;
	}
}
