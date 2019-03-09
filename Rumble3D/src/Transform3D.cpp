#include "R3D/Transform3D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace r3
{
	Transform3D::Transform3D(const glm::vec3& position,
							 const glm::mat3& rotation)
		: m_position{position}
	{
		m_rotation = glm::quat_cast(rotation);
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

	void Transform3D::translate(real x, real y, real z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
	}

	void Transform3D::rotate(const glm::quat& rot)
	{
		//m_rotation = rot * m_rotation;
		//m_rotation = m_rotation * rot;
		m_rotation = rot * m_rotation;
	}

	void Transform3D::rotate(const glm::mat3& rot)
	{
		m_rotation = glm::quat_cast(rot) * m_rotation;
	}

	void Transform3D::setRotation(const float w, const float x, const float y, const float z)
	{
		setRotation(glm::quat(w, x, y, z));
	}

	void Transform3D::setRotation(const glm::quat& orientation)
	{
		m_rotation = glm::toMat3(orientation);
	}

	void Transform3D::setRotation(const glm::mat3& rot)
	{
		m_rotation = rot;
	}

	glm::mat3 Transform3D::getRotationMat() const
	{
		return glm::mat3_cast(m_rotation);
	}

	const glm::quat& Transform3D::getRotation() const
	{
		return m_rotation;
	}

	void Transform3D::updateOrientationByAngularVelocity(const glm::vec3& rotation,
														 real duration)
	{
		auto rot = glm::quat(0, rotation * duration) * m_rotation * real(0.5);
		m_rotation += rot;
		m_rotation = glm::normalize(m_rotation);
	}

	glm::vec3 Transform3D::getPointInLocalSpace(const glm::vec3& point) const
	{
		glm::vec3 temp = point;
		temp -= m_position;
		return glm::inverse(m_rotation) * temp;
	}

	glm::vec3 Transform3D::getPointInWorldSpace(const glm::vec3& point) const
	{
		return m_rotation * point + m_position;
	}

	glm::vec3 Transform3D::getDirectionInLocalSpace(const glm::vec3& direction) const
	{
		return glm::inverse(m_rotation) * direction;
	}

	glm::vec3 Transform3D::getDirectionInWorldSpace(const glm::vec3& direction) const
	{
		return m_rotation * direction;
	}

	void Transform3D::reset(const glm::vec3& position,
							const glm::vec3& rotation)
	{
		m_position = position;
		m_rotation = rotation;
	}
}
