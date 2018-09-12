#pragma once
#include "R3D/Common/Common.h"
#include "IBoxBoxNarrowAlgorithm.h"

namespace r3
{
	class R3D_DECLSPEC BoxBoxNarrowAlgorithm : public IBoxBoxNarrowAlgorithm
	{
	public:
		explicit BoxBoxNarrowAlgorithm();
		~BoxBoxNarrowAlgorithm();

	protected:
		bool generateContactData(CollisionBox* first,
								 CollisionBox* second,
								 CollisionData& collisionData) override;
	};
}