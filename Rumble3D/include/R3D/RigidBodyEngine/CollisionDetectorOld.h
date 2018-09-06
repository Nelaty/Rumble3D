#pragma once
#include "R3D/Common/Common.h"

#include "CollisionSphere.h"
#include "CollisionBox.h"
#include "CollisionPlane.h"
#include "CollisionDataOld.h"

#include <glm/glm.hpp>

namespace r3
{
	// \todo replace static methods with replaceable algorithms
	// Behälter für Kollisionsalgorithmen:
	class R3D_DECLSPEC CollisionDetectorOld
	{
	public:
		static unsigned sphereAndHalfSpace(const CollisionSphere &sphere,
										   const CollisionPlane &plane,
										   CollisionDataOld *data);

		static unsigned sphereAndTruePlane(const CollisionSphere &sphere,
										   const CollisionPlane &plane,
										   CollisionDataOld *data);

		static unsigned sphereAndSphere(const CollisionSphere &one,
										const CollisionSphere &two,
										CollisionDataOld *data);

		static unsigned boxAndHalfSpace(const CollisionBox &box,
										const CollisionPlane &plane,
										CollisionDataOld *data);

		static unsigned boxAndSphere(const CollisionBox &box,
									 const CollisionSphere &sphere,
									 CollisionDataOld *data);

		static unsigned boxAndBox(const CollisionBox &one,
								  const CollisionBox &two,
								  CollisionDataOld *data);

	private:
		static real transformToAxis(const CollisionBox &box,
									const glm::vec3 &axis);
		/*
		* Überlappen zweier Quader entlang einer Achse.
		* Rückgabe ist der Wert der Überlappung.
		* toCentre ist der Vektor zwischen den Quadern und wird
		* übergeben, um nicht immer neu berechnet werden zu müssen.
		*/
		static real penetrationOnAxis(const CollisionBox &one,
									  const CollisionBox &two,
									  const glm::vec3 &axis,
									  const glm::vec3 &toCentre);

		/**
		 * \brief SAT-Test, ob bzgl.einer Achse eine Überlappung stattfindet.
		 * \param smallestPenetration INOUT-Parameter
		 * \param smallestCase INOUT-Parameter
		 * \return True if there are overlapping axis, false otherwise
		 */
		static bool tryAxis(const CollisionBox &one,
							const CollisionBox &two,
							glm::vec3 axis,
							const glm::vec3& toCentre,
							unsigned index,
							real& smallestPenetration,
							unsigned &smallestCase);

		/* 
		 * Erstellt die Kontaktdaten für den Fall BoxBox-Kollision
		 * wenn der Kontakt Ecke-Fläche ist:
		 */
		static void fillPointFaceBoxBox(const CollisionBox &one,
										const CollisionBox &two,
										const glm::vec3 &toCentre,
										CollisionDataOld *data,
										unsigned best,
										real pen);

		/**
		 * \param useOne true und Kontaktpunkt außerhalb der Kante
		 * (Kante-Fläche-Kontakt) dann nehmen wir den Mittelpunkt
		 * von Quader 1, sonst von Quader 2.
		 */
		static glm::vec3 contactPoint(const glm::vec3 &pOne,	
									  const glm::vec3 &dOne,
									  real oneSize,
									  const glm::vec3 &pTwo,
									  const glm::vec3 &dTwo,
									  real twoSize,
									  bool useOne);
	};
}
