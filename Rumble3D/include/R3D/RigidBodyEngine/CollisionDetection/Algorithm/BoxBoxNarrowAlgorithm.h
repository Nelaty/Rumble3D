#pragma once
#include "R3D/Common/Common.h"
#include "IBoxBoxNarrowAlgorithm.h"

#include <glm/glm.hpp>

namespace r3
{
	/**
	 * \brief Default implementation for a box-box narrow algorithm.
	 */
	class R3D_DECLSPEC BoxBoxNarrowAlgorithm : public IBoxBoxNarrowAlgorithm
	{
	public:
		explicit BoxBoxNarrowAlgorithm();
		~BoxBoxNarrowAlgorithm();

	protected:
		bool generateContactDataImpl(RigidBody* rbBox1, CollisionBox* box1,
									 RigidBody* rbBox2, CollisionBox* box2,
									 CollisionData& collisionData) override;
	
	private:

		static real transformToAxis(const CollisionBox* box,
									const glm::vec3& axis);

		/**
		* Überlappen zweier Quader entlang einer Achse.
		* Rückgabe ist der Wert der Überlappung.
		* toCentre ist der Vektor zwischen den Quadern und wird
		* übergeben, um nicht immer neu berechnet werden zu müssen.
		*/
		static real penetrationOnAxis(const CollisionBox* one,
									  const CollisionBox* two,
									  const glm::vec3& axis,
									  const glm::vec3& toCentre);

		/**
		* \brief SAT-Test, ob bzgl.einer Achse eine Überlappung stattfindet.
		* \param smallestPenetration INOUT-Parameter
		* \param smallestCase INOUT-Parameter
		* \return True if there are overlapping axis, false otherwise
		*/
		static bool tryAxis(const CollisionBox* one,
							const CollisionBox* two,
							glm::vec3 axis,
							const glm::vec3& toCentre,
							unsigned index,
							real& smallestPenetration,
							unsigned &smallestCase);

		/**
		* Erstellt die Kontaktdaten für den Fall BoxBox-Kollision
		* wenn der Kontakt Ecke-Fläche ist:
		*/
		static void fillPointFaceBoxBox(const CollisionBox* box1,
										const CollisionBox* box2,
										const glm::vec3& toCentre,
										Contact* contact,
										unsigned best,
										real penetration);

		/**
		* \param useOne true und Kontaktpunkt außerhalb der Kante
		* (Kante-Fläche-Kontakt) dann nehmen wir den Mittelpunkt
		* von Quader 1, sonst von Quader 2.
		*/
		static glm::vec3 contactPoint(const glm::vec3& pOne,
									  const glm::vec3& dOne,
									  real oneSize,
									  const glm::vec3& pTwo,
									  const glm::vec3& dTwo,
									  real twoSize,
									  bool useOne);
	};
}