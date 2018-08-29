#pragma once
#include "IBoxBoxNarrowAlgorithm.h"

namespace rum
{
	class BoxBoxNarrowAlgorithm : public IBoxBoxNarrowAlgorithm
	{
	public:
		explicit BoxBoxNarrowAlgorithm();
		~BoxBoxNarrowAlgorithm();

		bool generateContactData(CollisionBox* first,
								 CollisionBox* second,
								 CollisionData& collisionData) override;
	};
}