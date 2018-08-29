#pragma once
#include "R3D/RigidBodyEngine/Contact.h"

#include <vector>

namespace rum
{
	struct CollisionData
	{
		std::vector<Contact> m_contactData;
		unsigned int m_contacts;
		unsigned int m_contactsMax;
	};
}
