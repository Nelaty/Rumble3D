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
		// Registriert ein Paar aus Teilchen und Kraftgenerator, der
		// auf dem Teilchen wirkt.
		void Add(RigidBody * rigidBody, ForceGenerator * fg);
		// Löscht einen Eintrag aus der Registry.
		void Remove(RigidBody * rigidBody, ForceGenerator * fg);
		// Löscht alle Einträge aus der Registry.
		void Clear();
		// Ruft alle Kraft-Generatoren auf, so dass diese die Kräfte
		// der zugehörenden Teilchen aktualisieren können.
		void UpdateForces(real duration);

	protected:
		// Ein Eintrag in der Registry:
		struct ForceRegistrationEntry 
		{
			RigidBody * rigidBody;
			ForceGenerator * forceGenerator;
		};

		// Die Registry:
		typedef std::vector<ForceRegistrationEntry> Registry;
		Registry registrations;

	};
}
