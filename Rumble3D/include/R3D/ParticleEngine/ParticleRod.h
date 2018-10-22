#pragma once
#include "ParticleLink.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class ParticleContact;

	/**
	 * \brief Abstract class, which creates a distance constraint 
	 * between two particles. A contact gets created if this constraint
	 * is not fulfilled.
	 */
	class R3D_DECLSPEC ParticleRod : public ParticleLink
	{
	public:
		virtual ~ParticleRod();

	protected:
		explicit ParticleRod();

		real m_distance{};
	};
}