#include "R3D/RigidBodyEngine/CollisionData.h"

namespace rum
{
	CollisionData::CollisionData()
	= default;

	CollisionData::~CollisionData()
	= default;

	bool CollisionData::hasUnusedContacts() const
	{
		return (m_contactsLeft > 0);
	}
	
	void CollisionData::reset(const unsigned maxContacts)
	{
		m_contactsLeft = maxContacts;
		m_contactCount = 0;
		m_contacts = m_contactArray;
	}
	
	void CollisionData::addContacts(const unsigned count)
	{
		// Reduzierung der freien Kontakte; ERhöhung der gefundenen Kontakte:
		m_contactsLeft -= count;
		m_contactCount += count;
	
		// Array weiterzählen:
		m_contacts += count;
	}
	
	int CollisionData::getContactsLeft() const
	{
		return m_contactsLeft;
	}
	
	Contact * CollisionData::getContacts() const
	{
		return m_contacts;
	}
	
	real CollisionData::getFriction() const
	{
		return m_friction;
	}
	
	real CollisionData::getRestitution() const
	{
		return m_restitution;
	}
	
	int CollisionData::getContactCount() const
	{
		return m_contactCount;
	}
}