#pragma once
#include "R3D/Common/Common.h"
#include "R3D/ParticleEngine/ParticleEngineCI.h"
#include "R3D/ParticleEngine/ParticleContactResolver.h"

#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	class ParticleContact;

	/**
	 * \brief Default implementation of the particle computation interface.
	 */
	class DefaultParticleEngineCI : public ParticleEngineCI
	{
	public:
		/**
		 * \brief DefaultParticleEngineCI constructor
		 * \param contactsMax Maximal number of contacts, which can
		 * exist at the same time.
		 * \param iterations Maximal number of iterations the particle
		 * contact generator can use.
		 * \param particleWorld The particle world, which should be used for
		 * calculations.
		 */
		explicit DefaultParticleEngineCI(unsigned contactsMax, 
										 unsigned iterations = 0,
										 ParticleWorld* particleWorld = nullptr);
		~DefaultParticleEngineCI();

		void onBegin() override;
		/**
		 * \brief Update particle forces.
		 * \param timeDelta Time step of this update.
		 */
		void step(real timeDelta) override;
		/**
		 * \brief Perform integration and solve collisions.
		 * \param timeDelta Time step of this update.
		 */
		void integrate(real timeDelta) override;
		/**
		 * \brief Clear force accumulators and reset contact data.
		 */
		void onEnd() override;

		/**
		 * \brief Reset the computation interface.
		 */
		void reset() override;

		/**
		 * \brief Set the maximal number of contacts that the collision
		 * solver can use.
		 * \param contactsMax The maximal number of contacts.
		 */
		void setContactsMax(unsigned contactsMax);

	protected:
		/**
		 * \brief Solve all previously generated particle contacts.
		 */
		void runCollisionSolver(real timeDelta);
		/**
		 * \brief Generate particle contacts by using all registered
		 * particle contact generators.
		 */
		void generateContacts();

	private:
		ParticleContactResolver m_resolver;

		FixedSizeContainer<ParticleContact> m_contactData;

		unsigned int m_contactsMax;
		bool m_calculateIterations{};
		/** For ParticleContactResolver */
		unsigned int m_iterations;
	};
}
