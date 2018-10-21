#pragma once
#include "R3D/Common/Common.h"

#include "R3D/RigidBodyEngine/CollisionDetection/CollisionPair.h"

namespace r3
{
	class RigidBody;
	
	template<class BoundingVolumeClass>
	class R3D_DECLSPEC BVHNode
	{
	public:
		BVHNode();
		BVHNode(BVHNode<BoundingVolumeClass>* parent,
				const BoundingVolumeClass& volume,
				RigidBody* body = nullptr);
		~BVHNode();

		/** 
		 * \brief Check if this node is a leaf node (= has no child nodes).
		 * \return True if it is a leaf node, false otherwise.
		 */
		bool isLeaf() const;
		// Identifiziert die möglichen Kontakte von diesem Knoten abwärts
		// im Baum. Diese werden in das array contacts geschrieben (bis
		// Anzahl = limit). Rückgabe ist die Anzahl der gefundenen Kontakte.
		unsigned getPotentialContacts(CollisionPair* contacts,
									  unsigned limit) const;
	protected:
		// Gibt true zurück, wenn das eigene Volume mit dem Volume von other
		// überlappt, und false sonst.
		bool overlaps(BVHNode<BoundingVolumeClass>* other) const;
		// Rekursiver Teil des Algorithmus auf den Kindern der Wurzel und 
		// deren Kinder.
		unsigned getPotentialContactsWith(BVHNode<BoundingVolumeClass>* other,
										  CollisionPair* contacts,
										  unsigned limit) const;
		void recalculateBoundingVolume();
		void insert(RigidBody* newBody, const BoundingVolumeClass& newVolume);

		BVHNode* m_parent;
		BVHNode* m_children[2];

		// Festkörper an diesem Knoten. Nur bei Blättern gesetzt, sonst NULL.
		RigidBody* m_body;
	
		// Bounding Volume, das alle Kinder umfasst.
		BoundingVolumeClass m_volume;	
	};
}
