#pragma once
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"

#include "R3D/Common/Common.h"

#include <vector>

namespace r3
{

	class R3D_DECLSPEC CollisionData
	{
	public:
		explicit CollisionData(unsigned int contactsMax = 1000, int iterations = 0);
		~CollisionData();

		void init(int contactsMax, int iterations);
		void reset();

		/** \brief Check if there is no more room for new contacts. */
		bool isFull() const;

		/** \brief Check if no contacts are used. */
		bool isEmpty() const;

		/** \brief Check how many contacts can still be inserted. */
		int getContactsLeft() const;
		/** \brief Check how many contacts have been inserted. */
		int getContactsUsed() const;
		/** \brief Get the maximal number of contacts. */
		int getSize() const;

		/** \brief Get the next available contact. Automatically uses it! 
		 * \return nullptr if all contacts are used, a available contact otherwise.
		 */
		Contact* getAvailableContact();
		/** \brief Get all contacts (only valid to a certain position) */
		std::vector<Contact>& getData();
		/** \brief Get all contacts (only valid to a certain position) */
		const std::vector<Contact>& getData() const;

		void prepareContacts(real timeDelta);

	private:
		std::vector<Contact> m_data;

		unsigned int m_contactsUsed{};
		unsigned int m_contactsMax{};
		int m_iterations{};
	};
}