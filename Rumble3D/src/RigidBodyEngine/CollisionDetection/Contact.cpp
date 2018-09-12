#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	Contact::Contact()
	= default;

	Contact::~Contact()
	= default;

	RigidBody* Contact::getFirst() const
	{
		return m_pair.m_first;
	}

	RigidBody* Contact::getSecond() const
	{
		return m_pair.m_second;
	}
}
