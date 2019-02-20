#pragma once
#include "ParticleContactGenerator.h"
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	class Particle;
	class ParticleContact;

	/**
	 * \brief Abstract class. A ParticleLink links two particles.
	 */
	class R3D_DECLSPEC ParticleLink : public ParticleContactGenerator
	{
	public:
		virtual ~ParticleLink();

		/**
		 * \brief Change the referenced particles
		 * \param first First particle
		 * \param second Second particle
		 */
		void setParticles(Particle* first, Particle* second);

		/** \brief Get the first particle. */
		Particle* getFirst() const;

		/** \brief Get the second particle. */
		Particle* getSecond() const;

	protected:
		explicit ParticleLink();

		/**
		 * \brief Calculate the length between the current particles.
		 * \return The calculated length.
		 */
		real currentLength() const;

		Particle* m_particles[2]{};		
	};
}
