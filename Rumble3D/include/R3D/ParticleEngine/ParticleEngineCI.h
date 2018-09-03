#pragma once
#include "R3D/Common/Common.h"
#include "R3D/IComputationInterface.h"

/**
 * \brief Abstract class for computation interfaces used for particle worlds.
 */
namespace r3
{
	class ParticleWorld;

	class R3D_DECLSPEC ParticleEngineCI : public IComputationInterface
	{
	public:
		virtual ~ParticleEngineCI();

		/** Set the particle world, used for particle calculations. */
		void setParticleWorld(ParticleWorld* particleWorld);
		/** Get the currently used particle world. */
		ParticleWorld* getParticleWorld() const;

	protected:
		explicit ParticleEngineCI(ParticleWorld* particleWorld = nullptr);

		ParticleWorld* m_particleWorld;
	};
}