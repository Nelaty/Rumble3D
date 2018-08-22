#include "R3D/RigidBodyEngine/CollisionBox.h"

namespace rum
{
	CollisionBox::CollisionBox(RigidBody* body, const glm::mat4& offset, const glm::vec3& halfSize)
		: m_halfSize{halfSize}
	{
		m_body = body;
		m_offset = offset;
	}
	
	CollisionBox::~CollisionBox()
	= default;

	glm::vec3 CollisionBox::getHalfSize() const{
		return m_halfSize;
	}
	
	void CollisionBox::initVertices()
	{
		m_vertices =
		{
			glm::vec3(-m_halfSize.x, -m_halfSize.y, -m_halfSize.z),
			glm::vec3(-m_halfSize.x, -m_halfSize.y, +m_halfSize.z),
			glm::vec3(-m_halfSize.x, +m_halfSize.y, -m_halfSize.z),
			glm::vec3(-m_halfSize.x, +m_halfSize.y, +m_halfSize.z),
			glm::vec3(+m_halfSize.x, -m_halfSize.y, -m_halfSize.z),
			glm::vec3(+m_halfSize.x, -m_halfSize.y, +m_halfSize.z),
			glm::vec3(+m_halfSize.x, +m_halfSize.y, -m_halfSize.z),
			glm::vec3(+m_halfSize.x, +m_halfSize.y, +m_halfSize.z)
		};
		for(auto& vertex : m_vertices)
		{
			vertex = glm::vec3(m_offset * glm::vec4(vertex, static_cast<real>(1.0f)));
		}
	}
}