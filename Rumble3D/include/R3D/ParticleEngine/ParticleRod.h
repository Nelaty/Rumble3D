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
		virtual ~ParticleRod();

	protected:
		explicit ParticleRod();

		real m_length{}; // Abstand der Teilchen;
	};
}