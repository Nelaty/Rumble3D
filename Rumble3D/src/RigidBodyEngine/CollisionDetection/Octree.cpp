#include "R3D/RigidBodyEngine/CollisionDetection/Octree.h"

namespace r3
{	
	namespace detail
	{
		void OctreeNode::expand()
		{
			m_children.resize(8);
		}
	}

	void Octree::insert(RigidBody* rigidBody)
	{
		
	}

	void Octree::collectCollisionPairs(const InsertFunction& func) const
	{

	}
}
