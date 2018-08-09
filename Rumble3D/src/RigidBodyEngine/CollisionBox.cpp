#include "R3D/RigidBodyEngine/CollisionBox.h"

namespace rum
{
	CollisionBox::CollisionBox(RigidBody * _body, glm::mat4 _offset, glm::vec3 _halfsize)
	{
		m_body = _body;
		m_offset = _offset;
		m_halfSize = _halfsize;
	}
	
	CollisionBox::~CollisionBox()
	{
	}

	glm::vec3 CollisionBox::getHalfSize() const{
		return m_halfSize;
	}
	
	void CollisionBox::initVertices(){
		glm::vec3 vertices[8] = {
			glm::vec3(-m_halfSize.x, -m_halfSize.y, -m_halfSize.z),
			glm::vec3(-m_halfSize.x, -m_halfSize.y, +m_halfSize.z),
			glm::vec3(-m_halfSize.x, +m_halfSize.y, -m_halfSize.z),
			glm::vec3(-m_halfSize.x, +m_halfSize.y, +m_halfSize.z),
			glm::vec3(+m_halfSize.x, -m_halfSize.y, -m_halfSize.z),
			glm::vec3(+m_halfSize.x, -m_halfSize.y, +m_halfSize.z),
			glm::vec3(+m_halfSize.x, +m_halfSize.y, -m_halfSize.z),
			glm::vec3(+m_halfSize.x, +m_halfSize.y, +m_halfSize.z)
		};
		for (unsigned i = 0; i < 8; i++)
		{
			vertices[i] = glm::vec3(m_offset * glm::vec4(vertices[i], static_cast<real>(1.0f)));
		}
	}
}