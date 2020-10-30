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

	Octree::Octree()
		= default;

	Octree::~Octree()
		= default;

	void Octree::insert(RigidBody* rigidBody)
	{
		
	}

	void Octree::collectCollisionPairs(const InsertFunction& func) const
	{

	}
}
