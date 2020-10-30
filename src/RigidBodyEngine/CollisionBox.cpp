#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	CollisionBox::CollisionBox(RigidBody* body,
							   const glm::vec3& halfSizes,
							   const glm::mat4& offset)
		: CollisionPrimitive(R3D_PRIMITIVE_BOX),
		m_halfSizes{halfSizes}
	{
		m_body = body;
		m_offset = offset;

		initVertices();
	}

	CollisionBox::~CollisionBox()
		= default;

	const glm::vec3& CollisionBox::getHalfSize() const
	{
		return m_halfSizes;
	}

	void CollisionBox::initVertices()
	{
		m_vertices =
		{
			glm::vec3(-m_halfSizes.x, -m_halfSizes.y, -m_halfSizes.z),
			glm::vec3(-m_halfSizes.x, -m_halfSizes.y, +m_halfSizes.z),
			glm::vec3(-m_halfSizes.x, +m_halfSizes.y, -m_halfSizes.z),
			glm::vec3(-m_halfSizes.x, +m_halfSizes.y, +m_halfSizes.z),
			glm::vec3(+m_halfSizes.x, -m_halfSizes.y, -m_halfSizes.z),
			glm::vec3(+m_halfSizes.x, -m_halfSizes.y, +m_halfSizes.z),
			glm::vec3(+m_halfSizes.x, +m_halfSizes.y, -m_halfSizes.z),
			glm::vec3(+m_halfSizes.x, +m_halfSizes.y, +m_halfSizes.z)
		};
		for(auto& vertex : m_vertices)
		{
			vertex = glm::vec3(m_offset * glm::vec4(vertex, static_cast<real>(1.0f)));
		}
	}
}
