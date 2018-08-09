#include "R3D/RigidBodyEngine/BVHNode.h"
#include "R3D/RigidBodyEngine/BoundingSphere.h"
#include "R3D/RigidBodyEngine/BoundingBox.h"

namespace rum
{
	template<class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::BVHNode()
	{
	}

	template<class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::BVHNode(BVHNode<BoundingVolumeClass> *parent, const BoundingVolumeClass &volume,
										  RigidBody* body)
		: m_parent(parent),
		m_volume(volume),
		m_body(body)
	{
		m_children[0] = m_children[1] = nullptr;
	}

	template<class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::~BVHNode()
	{
		// Ohne Eltern müssen wir uns um Geschwister nicht kümmern.
		if(m_parent)
		{
			// Suche Geschwister
			BVHNode<BoundingVolumeClass> *sibling;
			if(m_parent->m_children[0] == this)
			{
				sibling = m_parent->m_children[1];
			}
			else
			{
				sibling = m_parent->m_children[0];
			}

			// Überschreibe Elternknoten mit Geschwisterdaten
			m_parent->m_volume = sibling->m_volume;
			m_parent->m_body = sibling->m_body;
			m_parent->m_children[0] = sibling->m_children[0];
			m_parent->m_children[1] = sibling->m_children[1];

			// Lösche das ursprünglicheGeschwisterojekt.
			sibling->m_parent = nullptr;
			sibling->m_body = nullptr;
			sibling->m_children[0] = nullptr;
			sibling->m_children[1] = nullptr;
			delete sibling;

			// Eltern Volumen neu berechnen:
			m_parent->RecalculateBoundingVolume();
		}

		// Lösche Kinder.
		if(m_children[0])
		{
			m_children[0]->m_parent = nullptr;
			delete m_children[0];
		}
		if(m_children[1])
		{
			m_children[1]->m_parent = nullptr;
			delete m_children[1];
		}
	}


	template<class BoundingVolumeClass>
	bool BVHNode<BoundingVolumeClass>::IsLeaf() const
	{
		return (m_body != nullptr);
	}

	template<class BoundingVolumeClass>
	unsigned int BVHNode<BoundingVolumeClass>::GetPotentialContacts(PotentialContacts * contacts,
																	unsigned int limit) const
	{
		// Ende, wenn Blatt, oder Limit erreicht.
		if(IsLeaf() || limit == 0)
		{
			return 0;
		}

		// Potentielle Kontakte eines unserer Kinder mit dem anderen.
		return m_children[0]->GetPotentialContactsWith(m_children[1], contacts, limit);
	}

	template<class BoundingVolumeClass>
	bool BVHNode<BoundingVolumeClass>::Overlaps(BVHNode<BoundingVolumeClass> * other) const
	{
		return m_volume.Overlaps(&(other->m_volume));
	}

	template<class BoundingVolumeClass>
	unsigned BVHNode<BoundingVolumeClass>::GetPotentialContactsWith(
		BVHNode<BoundingVolumeClass> * other,
		PotentialContacts * contacts,
		unsigned limit) const{

		// Ende, wenn Blatt, oder Limit erreicht.
		if(!Overlaps(other) || limit == 0)
		{
			return 0;
		}

		// Wenn beides Blätter, dann potentieller Kontakt:
		if(IsLeaf() && other->IsLeaf())
		{
			contacts->bodies[0] = m_body;
			contacts->bodies[1] = other->m_body;
			return 1;
		}

		// Absteigen im Baum. Ist eines ein Blatt, steigen wir den
		// anderen Zweig ab. Sind beides Zweige, dann steigen wir den
		// mit größtem Volumen ab:
		if(other->IsLeaf() ||
			(!IsLeaf() && m_volume.GetSize() >= other->m_volume.GetSize()))
		{
			// Rekursion in children[0]:
			unsigned count = m_children[0]->GetPotentialContactsWith(other, contacts, limit);

			// Rekursion in andere Seite, wenn genügend PLatz im Array:
			if(limit > count)
			{
				return count + m_children[1]->GetPotentialContactsWith(
					other, contacts + count, limit - count);
			}
			else
			{
				return count;
			}
		}
		else
		{
			// Rekursion in children[0] von other:
			unsigned count = GetPotentialContactsWith(other->m_children[0], contacts, limit);

			// Rekursion in andere Seite, wenn genügend PLatz im Array:
			if(limit > count)
			{
				return count + GetPotentialContactsWith(
					other->m_children[1], contacts + count, limit - count);
			}
			else
			{
				return count;
			}
		}
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::RecalculateBoundingVolume()
	{
		if(IsLeaf())
		{
			return;
		}

		m_volume = BoundingVolumeClass(
			m_children[0]->m_volume,
			m_children[1]->m_volume
		);

		// Rekursion
		if(m_parent)
		{
			m_parent->RecalculateBoundingVolume();
		}
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::Insert(
		RigidBody* newBody, const BoundingVolumeClass &newVolume
	)
	{
		// Wenn this ein Blatt ist, brauchen wir zwei Kinder, eines
		// mit this und das andere mit newBody
		if(IsLeaf())
		{
			// Kopie von this in Kind_0.
			m_children[0] = new BVHNode<BoundingVolumeClass>(this, m_volume, m_body);

			// Kind2 ist neuer Festkörper
			m_children[1] = new BVHNode<BoundingVolumeClass>(this, newVolume, newBody);

			// And we now loose the body (we're no longer a leaf)
			this->m_body = nullptr;

			// We need to recalculate our bounding volume
			RecalculateBoundingVolume();
		}

		// Füge neuen Festkörper dort ein, wo resultierendes Volumen
		// am kleinsten ist:
		else
		{
			if(m_children[0]->m_volume.GetGrowth(newVolume) <
			   m_children[1]->m_volume.GetGrowth(newVolume))
			{
				m_children[0]->Insert(newBody, newVolume);
			}
			else
			{
				m_children[1]->Insert(newBody, newVolume);
			}
		}
	}

	// Widerspricht dem Template-Konzept, sorgt jedoch für
	// Information Hiding der Implementierung. Es dürfen seitens
	// der Nutzer der Klasse lediglich Instanzen mit aktuellem
	// Klassenparameter BoundingSphere gebildet werden.
	template class BVHNode<BoundingSphere>;
	template class BVHNode<BoundingBox>;
}