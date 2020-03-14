#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

#include <vector>

namespace r3
{
	class RigidBody;
	class ForceGenerator;

	/**
	 * \brief Pairs force generators with rigid bodies. It uses the
	 * force generators to update forces of linked rigid bodies.
	 */
	class R3D_DECLSPEC ForceRegistry
	{
	public:
		struct ForceRegistrationEntry
		{
			RigidBody* m_rigidBody;
			ForceGenerator* m_forceGenerator;
		};
		using Registry = std::vector<ForceRegistrationEntry>;

		explicit ForceRegistry();
		~ForceRegistry();

		/**
		 * \brief Register a pair of rigid body and force generator.
		 * \param rigidBody The rigid body part of the pair.
		 * \param generator The force generator part of the pair.
		 */
		void registerForce(RigidBody* rigidBody, ForceGenerator* generator);
		/**
		 * \brief Remove a force registration entry from the registry.
		 * \param rigidBody The rigid body part of the entry.
		 * \param generator The generator part of the entry.
		 */
		void unregisterForce(RigidBody* rigidBody, ForceGenerator* generator);
		/**
		 * \brief Remove all entries from the registry.
		 */
		void clear();
		/**
		 * \brief Use registered force generators to apply forces to
		 * rigid bodies, which they are paired up with.
		 */
		void updateForces();

	protected:	
		Registry m_registrations;
	};
}
