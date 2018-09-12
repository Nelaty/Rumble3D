#pragma once
#include "ContactOld.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ContactOld;

	class R3D_DECLSPEC CollisionDataOld
	{
	public:
		explicit CollisionDataOld();
		~CollisionDataOld();

		// Gibt true zurück, wenn noch freie Plätze im Array vorhanden sind
		// und sonst false.
		bool hasUnusedContacts() const;
		// Zurücksetzen des Arrays, so dass keine Kontakte gespeichert sind.
		void reset(unsigned maxContacts);

		// Indexverwaltung, wenn neue Kontakte hinzukamen.
		void addContacts(unsigned count);
		int getContactsLeft() const;
		ContactOld* getContacts() const;

		real getFriction() const;
		real getRestitution() const;
		int getContactCount() const;

	protected:
		ContactOld* m_contactArray{};   // Erstes Array-Element;
		ContactOld* m_contacts{};       // Array-Eintrag;
		int m_contactsLeft{};         // Anzahl der Kontakte, die im Array noch frei sind;
		unsigned m_contactCount{};    // Anzahl der bereits gefundenen Kontakte;
		real m_friction = 0.5f;     // Reibung für alle Kontakte;
		real m_restitution = 0.5f;  // Restitution für alle Kontakte;
	};
}
