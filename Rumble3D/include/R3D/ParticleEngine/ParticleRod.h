#pragma once
#include "ParticleLink.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ParticleContact;

	// Feste Verbindung zweier Teilchen. 
	// Erzeugt Kontact, wenn sich ihr Abstand verändert.
	class R3D_DECLSPEC ParticleRod : public ParticleLink
	{
	public:
		virtual ~ParticleRod();

	protected:
		explicit ParticleRod();

		real m_length{}; // Abstand der Teilchen;
	};
}