#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"
#include "R3D/ParticleEngine/ParticleContactGenerator.h"

#include <utility>

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
		virtual ~ParticleLink() = default;

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
		explicit ParticleLink() = default;

		/**
		 * \brief Calculate the length between the current particles.
		 * \return The calculated length.
		 */
		real currentLength() const;

		std::pair<Particle*, Particle*> m_particles{};
	};
}
