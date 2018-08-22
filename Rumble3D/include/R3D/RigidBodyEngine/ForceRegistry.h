#pragma once
#include "R3D/Common/Precision.h"

#include <vector>

namespace rum
{
	class RigidBody;
	class ForceGenerator;

	class ForceRegistry
	{
	public:
		/** A entry of the ForceRegistry. */
		struct ForceRegistrationEntry
		{
			RigidBody* m_rigidBody;
			ForceGenerator* m_forceGenerator;
		};

		using Registry = std::vector<ForceRegistrationEntry>;

		explicit ForceRegistry();
		~ForceRegistry();

		// Registriert ein Paar aus Teilchen und Kraftgenerator, der
		// auf dem Teilchen wirkt.
		void registerForce(RigidBody* rigidBody, ForceGenerator * fg);
		// Löscht einen Eintrag aus der Registry.
		void unregisterForce(RigidBody* rigidBody, ForceGenerator * fg);
		// Löscht alle Einträge aus der Registry.
		void clear();
		// Ruft alle Kraft-Generatoren auf, so dass diese die Kräfte
		// der zugehörenden Teilchen aktualisieren können.
		void updateForces(real duration);

	protected:	
		Registry m_registrations;
	};
}
