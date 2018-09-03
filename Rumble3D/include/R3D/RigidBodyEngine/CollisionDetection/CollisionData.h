#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/Contact.h"

#include <vector>

namespace r3
{
	struct R3D_DECLSPEC CollisionData
	{
		std::vector<Contact> m_contactData;
		unsigned int m_contacts;
		unsigned int m_contactsMax;
	};
}
