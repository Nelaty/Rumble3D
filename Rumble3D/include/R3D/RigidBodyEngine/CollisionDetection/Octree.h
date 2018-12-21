#pragma once
#include "R3D/Common/Common.h"

#include <vector>
#include <functional>

namespace r3
{
	class RigidBody;

	namespace detail
	{
		class OctreeNode
		{
		public:
			explicit OctreeNode();
			~OctreeNode();

			void expand();


		private:
			std::vector<OctreeNode> m_children;
		};
	}
	
	class R3D_DECLSPEC Octree
	{
	public:
		using InsertFunction = std::function<void(RigidBody*, RigidBody*)>;

		explicit Octree();
		~Octree();

		void insert(RigidBody* rigidBody);
		void collectCollisionPairs(const InsertFunction& func) const;

	private:
		detail::OctreeNode m_root;
	};
}