#pragma once
#include "ParticleLink.h"
#include "R3D/Common/Precision.h"

namespace rum
{
	class ParticleContact;

	// Feste Verbindung zweier Teilchen. 
	// Erzeugt Kontact, wenn sich ihr Abstand verändert.
	class ParticleRod :	public ParticleLink
	{
	public:
		// Erzeugt einen Kontakt, um das Tau daran zu 
		// hindern, über die Mamimallänge hinaus angespannt 
		// zu werden, indem sich die beiden verbundenen 
		// Teilchen zu weit voneinander entfernen.
		unsigned int AddContact(ParticleContact* contact, unsigned int limit) const override;
	
	protected:
		real m_length; // Abstand der Teilchen;
	};
}