#include "R3D/RigidBodyEngine/CollisionDetection/CollisionData.h"
#include <cassert>

namespace r3
{
	CollisionData::CollisionData(const unsigned contactsMax,
	                             const int iterations)
	{
		init(contactsMax, iterations);
	}

	CollisionData::~CollisionData()
	= default;

	void CollisionData::init(const int contactsMax,
							 const int iterations)
	{
		assert(contactsMax > 0);

		m_data.resize(contactsMax);
		m_contactsMax = contactsMax;
		m_iterations = iterations;

		reset();
	}

	void CollisionData::reset()
	{
		m_contactsUsed = 0;
	}

	bool CollisionData::isFull() const
	{
		return m_contactsUsed == m_contactsMax;
	}

	bool CollisionData::isEmpty() const
	{
		return m_contactsUsed == 0;
	}

	int CollisionData::getContactsLeft() const
	{
		return m_contactsMax - m_contactsUsed;
	}

	int CollisionData::getContactsUsed() const
	{
		return m_contactsUsed;
	}

	int CollisionData::getSize() const
	{
		return m_contactsMax;
	}

	Contact* CollisionData::getAvailableContact()
	{
		if(isFull()) return nullptr;

		const auto result = &m_data[m_contactsUsed];
		++m_contactsUsed;
		return result;
	}

	std::vector<Contact>& CollisionData::getData()
	{
		return m_data;
	}

	const std::vector<Contact>& CollisionData::getData() const
	{
		return m_data;
	}

	void CollisionData::prepareContacts(const real timeDelta)
	{
		for(unsigned i = 0; i < m_contactsUsed; ++i)
		{
			m_data[i].calculateInternals(timeDelta);
		}
	}
}
