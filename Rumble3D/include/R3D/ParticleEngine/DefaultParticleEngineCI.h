#pragma once
#include "R3D/Common/Common.h"
#include "R3D/ParticleEngine/ParticleEngineCI.h"
#include "R3D/ParticleEngine/ParticleContactResolver.h"

namespace r3
{
	class ParticleContact;

	class R3D_DECLSPEC DefaultParticleEngineCI : public ParticleEngineCI
	{
	public:
		explicit DefaultParticleEngineCI(unsigned int maxContacts, 
										 unsigned int iterations = 0,
										 ParticleWorld* particleWorld = nullptr);
		~DefaultParticleEngineCI();

		void onBegin() override;
		void step(real timeDelta) override;
		void integrate(real timeDelta) override;
		void onEnd() override;

		void reset() override;

	protected:
		void runCollisionSolver(real timeDelta);
		unsigned generateContacts() const;

	private:
		ParticleContactResolver m_resolver;
		ParticleContact* m_contacts;

		unsigned int m_maxContacts;
		bool m_calculateIterations;
		/** For ParticleContactResolver */
		unsigned int m_iterations;
	};
}
