#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <vector>

namespace r3
{
	class Particle;
	class IParticleForceGenerator;

	/**
	 * \brief A ParticleForceRegistry contains a set of 
	 * ParticleForceGenerators and Particles they act on.
	 */
	class R3D_DECLSPEC ParticleForceRegistry
	{	
	public:
		struct ParticleForceRegistrationEntry
		{
			Particle* m_particle;
			IParticleForceGenerator* m_forceGenerator;
		};
		using Registry_Type = std::vector<ParticleForceRegistrationEntry>;

		explicit ParticleForceRegistry();
		~ParticleForceRegistry();

		/**
		 * \brief Register a force generator with a particle it acts on.
		 * \param particle The particle, which will receive forces.
		 * \param generator The force generator, which will act forces on
		 * the particle.
		 */
		void add(Particle* particle, IParticleForceGenerator* generator);
		/**
		 * \brief Remove an existing entry.
		 * \param particle The particle stored in the entry.
		 * \param generator The force generator stored in the entry.
		 * \return True if the given pair was found, false otherwise.
		 */
		bool remove(Particle* particle, IParticleForceGenerator* generator);
		/**
		 * \brief Remove all entries.
		 */
		void clear();
		/**
		 * \brief Let all registered force generators act forces on
		 * their linked particle(s).
		 */
		void updateForces();

	protected:
		Registry_Type m_registrations;
	};
}

