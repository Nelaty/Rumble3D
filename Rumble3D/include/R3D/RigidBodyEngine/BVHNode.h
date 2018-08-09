#pragma once
#include "RigidBody.h"

namespace rum
{
	struct PotentialContacts
	{
		RigidBody * bodies[2];
	};
	
	template<class BoundingVolumeClass>
	class BVHNode
	{
	public:
		BVHNode();
		BVHNode(BVHNode<BoundingVolumeClass> * parent,
			const BoundingVolumeClass & volume,
			RigidBody * body = nullptr);
		~BVHNode();

		bool IsLeaf() const;
		// Identifiziert die möglichen Kontakte von diesem Knoten abwärts
		// im Baum. Diese werden in das array contacts geschrieben (bis
		// Anzahl = limit). Rückgabe ist die Anzahl der gefundenen Kontakte.
		unsigned int GetPotentialContacts(PotentialContacts* contacts, 
										  unsigned int limit) const;
	protected:
		// Gibt true zurück, wenn das eigene Volume mit dem Volume von other
		// überlappt, und false sonst.
		bool Overlaps(BVHNode<BoundingVolumeClass> * other) const;
		// Rekursiver Teil des Algorithmus auf den Kindern der Wurzel und 
		// deren Kinder.
		unsigned GetPotentialContactsWith(
			BVHNode<BoundingVolumeClass> * other,
			PotentialContacts * contacts,
			unsigned limit) const;
		void RecalculateBoundingVolume();
		void Insert(RigidBody* newBody, const BoundingVolumeClass &newVolume);

		// Kindknoten dieses Knotens.
		BVHNode * m_children[2];
		// Bounding Volume, das alle Kinder umfasst.
		BoundingVolumeClass m_volume;
		// Festkörper an diesem Knoten. Nur bei Blättern
		// gesetzt, sonst NULL.
		RigidBody * m_body;
		// Elternknoten im Baum:
		BVHNode * m_parent;
	};
}
