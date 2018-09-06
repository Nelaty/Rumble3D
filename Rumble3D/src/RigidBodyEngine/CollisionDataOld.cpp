#include "R3D/RigidBodyEngine/CollisionDataOld.h"

namespace r3
{
	CollisionDataOld::CollisionDataOld()
	= default;

	CollisionDataOld::~CollisionDataOld()
	= default;

	bool CollisionDataOld::hasUnusedContacts() const
	{
		return (m_contactsLeft > 0);
	}
	
	void CollisionDataOld::reset(const unsigned maxContacts)
	{
		m_contactsLeft = maxContacts;
		m_contactCount = 0;
		m_contacts = m_contactArray;
	}
	
	void CollisionDataOld::addContacts(const unsigned count)
	{
		// Reduzierung der freien Kontakte; ERhöhung der gefundenen Kontakte:
		m_contactsLeft -= count;
		m_contactCount += count;
	
		// Array weiterzählen:
		m_contacts += count;
	}
	
	int CollisionDataOld::getContactsLeft() const
	{
		return m_contactsLeft;
	}
	
	Contact * CollisionDataOld::getContacts() const
	{
		return m_contacts;
	}
	
	real CollisionDataOld::getFriction() const
	{
		return m_friction;
	}
	
	real CollisionDataOld::getRestitution() const
	{
		return m_restitution;
	}
	
	int CollisionDataOld::getContactCount() const
	{
		return m_contactCount;
	}
}