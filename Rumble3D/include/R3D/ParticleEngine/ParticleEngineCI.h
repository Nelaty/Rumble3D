#pragma once
#include "R3D/Common/Common.h"
#include "R3D/IComputationInterface.h"

namespace r3
{
	class ParticleWorld;

	/**
	* \brief Abstract class for computation interfaces used for particle worlds.
	*/
	class R3D_DECLSPEC ParticleEngineCI : public IComputationInterface
	{
	public:
		virtual ~ParticleEngineCI() = default;

		/** 
		 * \brief Set the particle world, used for particle calculations. 
		 * \param particleWorld The particle world, which should be used for
		 * calculations.
		 */
		void setParticleWorld(ParticleWorld* particleWorld);
		/** 
		 * \brief Get the particle world.
		 * \return The currently used particle world.
		 */
		ParticleWorld* getParticleWorld() const;

	protected:
		/**
		 * \brief ParticleEngineCI constructor
		 * \param particleWorld The particle world, which should be used for
		 * calculations.
		 */
		explicit ParticleEngineCI(ParticleWorld* particleWorld = nullptr);

		ParticleWorld* m_particleWorld;
	};
}