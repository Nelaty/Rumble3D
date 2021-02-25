#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionResolution/ICollisionResolutionFilter.h"
#include "R3D/RigidBodyEngine/CollisionDetection/Contact.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	/**
	 * \brief Specialized collision resolution filter, which solves
	 * interpenetration of bodies.
	 */
	class R3D_DECLSPEC InterpenetrationResolver : public ICollisionResolutionFilter
	{
	public:
		explicit InterpenetrationResolver();
		~InterpenetrationResolver() = default;

		void resolve(FixedSizeContainer<Contact>& collisionData,
					 real timeDelta) override;

		void setMaxIterations(unsigned int iterations);
		void setPositionEpsilon(real epsilon);

	private:
		void adjustPositions(FixedSizeContainer<Contact>& collisionData, real timeDelta);

		void applyPositionChange(glm::vec3 linearChange[2],
								 glm::vec3 angularChange[2],
								 const Contact& contact) const;

		real m_epsilon;

		unsigned int m_iterationsUsed;
		unsigned int m_iterations;
	};
}