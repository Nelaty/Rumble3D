#include "R3D/RigidBodyEngine/BVHNode.h"
#include "R3D/RigidBodyEngine/BoundingSphere.h"
#include "R3D/RigidBodyEngine/BoundingBox.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace r3
{
	namespace
	{
		template<class T>
		class has_overlap_method
		{
			template<typename U, bool (U::*)(const U*) const> struct checker {};
			template<typename U> static char test(checker<U, &U::overlap>*);
			template<typename U> static int test(...);

		public:
			static const bool value = sizeof(test<T>(nullptr)) == sizeof(char);
		};
	}

	template<class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::BVHNode()
	= default;

	template<class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::BVHNode(BVHNode<BoundingVolumeClass>* parent, 
										  const BoundingVolumeClass& volume,
										  RigidBody* body)
		: m_parent(parent),
		m_body(body),
		m_volume(volume)
	{
		//static_assert(has_overlap_method<BoundingVolumeClass>::value,
		//			  "Bounding volume class doens't support overlap method!");
	}

	template<class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::~BVHNode()
	{
		auto* sibling = getSibling();
		if(sibling)
		{
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
			m_parent->recalculateBoundingVolume();
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
	bool BVHNode<BoundingVolumeClass>::isLeaf() const
	{
		return m_body != nullptr;
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::getPotentialContacts(FixedSizeContainer<CollisionPair>& contacts) const
	{
		if(isLeaf() || contacts.isFull())
		{
			return;
		}

		// Potentielle Kontakte eines unserer Kinder mit dem anderen.
		m_children[0]->getPotentialContactsWith(m_children[1], contacts);
	}

	template <class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>* BVHNode<BoundingVolumeClass>::getSibling() const
	{
		if(!m_parent)
		{
			return nullptr;
		}

		if (this == m_parent->m_children[0])
		{
			return m_parent->m_children[1];
		}
		return m_parent->m_children[0];

	}

	template<class BoundingVolumeClass>
	bool BVHNode<BoundingVolumeClass>::overlaps(BVHNode<BoundingVolumeClass> * other) const
	{
		return m_volume.overlaps(&(other->m_volume));
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::getPotentialContactsWith(BVHNode<BoundingVolumeClass>* other,
																FixedSizeContainer<CollisionPair>& contacts) const
	{
		if(!overlaps(other) || contacts.isFull()) return;

		/** Potential contact if both are leaf nodes. */
		if(isLeaf() && other->isLeaf())
		{
			auto entry = contacts.getAvailableEntry();
			entry->init(m_body, other->m_body);
			return;
		}

		/** Recursively get potential contacts with child nodes. */
		if(other->isLeaf() ||
			(!isLeaf() && m_volume.getVolume() >= other->m_volume.getVolume()))
		{
			m_children[0]->getPotentialContactsWith(other, contacts);
			m_children[1]->getPotentialContactsWith(other, contacts);
			return;
		}
		
		getPotentialContactsWith(other->m_children[0], contacts);
		getPotentialContactsWith(other->m_children[1], contacts);
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::recalculateBoundingVolume()
	{
		if(isLeaf()) return;

		m_volume = BoundingVolumeClass(m_children[0]->m_volume,
									   m_children[1]->m_volume);

		if(m_parent)
		{
			m_parent->recalculateBoundingVolume();
		}
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::insert(RigidBody* newBody, 
											  const BoundingVolumeClass &newVolume)
	{
		// Wenn this ein Blatt ist, brauchen wir zwei Kinder, eines
		// mit this und das andere mit newBody
		if(isLeaf())
		{
			// Kopie von this in Kind_0.
			m_children[0] = new BVHNode<BoundingVolumeClass>(this, m_volume, m_body);

			// Kind2 ist neuer Festkörper
			m_children[1] = new BVHNode<BoundingVolumeClass>(this, newVolume, newBody);

			// And we now loose the body (we're no longer a leaf)
			m_body = nullptr;

			recalculateBoundingVolume();
		}

		// Füge neuen Festkörper dort ein, wo resultierendes Volumen
		// am kleinsten ist:
		else
		{
			if(m_children[0]->m_volume.getGrowth(newVolume) <
			   m_children[1]->m_volume.getGrowth(newVolume))
			{
				m_children[0]->insert(newBody, newVolume);
			}
			else
			{
				m_children[1]->insert(newBody, newVolume);
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