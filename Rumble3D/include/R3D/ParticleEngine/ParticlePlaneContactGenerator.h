#pragma once
#include "R3D/ParticleEngine/ParticleContactGenerator.h"

#include "R3D/Common/Precision.h"
#include "R3D/RigidBodyEngine/CollisionPlane.h"
#include "R3D/ParticleEngine/Particle.h"

namespace r3
{
    class ParticleContact;

	class R3D_DECLSPEC ParticlePlaneContactGenerator : public ParticleContactGenerator
	{
	public:
		ParticlePlaneContactGenerator(real restitution, real radius);
		~ParticlePlaneContactGenerator() = default;
	
		void addContact(FixedSizeContainer<ParticleContact>& contactData) const override;

		void setRestitution(real restitution);
		void setPlane(CollisionPlane* plane);
		void setParticle(Particle* particle);

	private:
		real m_restitution;
		Particle* m_particle{};
		real m_radius;
		CollisionPlane* m_plane{};
	};
}
