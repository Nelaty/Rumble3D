#pragma once
#include "R3D/Common/Common.h"
#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPair.h"
#include "R3D/Utility/FixedSizeContainer.h"

namespace r3
{
	class RigidBody;

	/**
	 * \breif Hierarchy of bounding volumes. Only leaf nodes describe
	 * actually collidable bounding volumes.
	 */
	template<class BoundingVolumeClass>
	class R3D_EXPORT BVHNode
	{
	public:
		BVHNode() = default;
		/**
		 * \brief BVHNode constructor.
		 * \param parent The parent bounding volume.
		 * \param volume The bounding volume of this node which,
		 * contains all child bounding volumes.
		 * \param body The rigid body represented by this node. Should be
		 * nullptr for non-leaf nodes.
		 */
		BVHNode(BVHNode<BoundingVolumeClass>* parent,
				const BoundingVolumeClass& volume,
				RigidBody* body = nullptr);
		~BVHNode();

		/** 
		 * \brief Check if this node is a leaf node (= has no child nodes).
		 * \return True if it is a leaf node, false otherwise.
		 */
		bool isLeaf() const;
		/**
		 * \brief Find all potential contacts in this bounding volume
		 * hierarchy.
		 * \param[out] contacts The resulting contacts.
		 */
		void getPotentialContacts(FixedSizeContainer<CollisionPair>& contacts) const;
		
	protected:
		/**
		 * \brief Get the sibling node of a child node.
		 * \return The sibling node or nullptr if this node has no parent.
		 */
		BVHNode<BoundingVolumeClass>* getSibling() const;
		
		/**
		 * \brief Check if there is a child node, that overlaps
		 * with the given node.
		 * \param other The other node to check against.
		 * \return True if there is a collision, false otherwise.
		 */
		bool overlaps(BVHNode<BoundingVolumeClass>* other) const;
		/**
		 * \brief Get all potential contacts with the given bounding
		 * volume.
		 * \param other The bounding volume to check against.
		 * \param[out] contacts The resulting contacts.
		 */
		void getPotentialContactsWith(BVHNode<BoundingVolumeClass>* other,
									  FixedSizeContainer<CollisionPair>&  contacts) const;
		/**
		 * \brief Recalculate all bounding volumes from this node 
		 * all the way up to the root node.
		 */
		void recalculateBoundingVolume();
		/**
		 * \brief Insert a new bounding volume into this BVH as a
		 * child node.
		 * \param newBody The rigid body to insert.
		 * \param newVolume The new volume to insert.
		 */
		void insert(RigidBody* newBody, const BoundingVolumeClass& newVolume);

		BVHNode* m_parent;
		BVHNode* m_children[2]{};

		/**
		 * \brief Only set for leaf nodes.
		 */
		RigidBody* m_body;

		/**
		 * \brief Bounding volume, which contains all child nodes.
		 */
		BoundingVolumeClass m_volume;	
	};
}
