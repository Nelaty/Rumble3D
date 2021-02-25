#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/BoxBoxNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <cassert>

namespace r3
{
    bool BoxBoxNarrowAlgorithm::generateContactDataImpl(RigidBody* rbBox1, CollisionBox* box1,
														RigidBody* rbBox2, CollisionBox* box2,
														FixedSizeContainer<Contact>& collisionData)
	{
		// Check if there is still a contact left
		if(collisionData.isFull())
		{
			return false;
		}

		// Vektor zwischen den Schwerpunkten:
		const glm::vec3 oneCentre = rbBox1->getTransform().getPosition();
		const glm::vec3 twoCentre = rbBox2->getTransform().getPosition();
		glm::vec3 toCentre = twoCentre - oneCentre;

		// Angenommen,es gibt keinen Kontakt:
		real pen = R3D_REAL_MAX;
		unsigned int best = 0xffffff;

		const auto checkOverlap = [&](const glm::vec3& axis, const unsigned int index)
		{
			return !tryAxis(box1, box2, axis, toCentre, index, pen, best);
		};

		// SAT-Test mit allen Achsen. Wenn ein Test positiv ist,
		// verlassen wir die Methode mit 0Kontakten.
		// Sonst suchen wir die Achsemit der minimalen Durchdringung:
		const auto& rotationOne = rbBox1->getTransform().getRotationMat();
		const auto& rotationTwo = rbBox2->getTransform().getRotationMat();

		if(checkOverlap(rotationOne[0], 0)) return false;
		if(checkOverlap(rotationOne[1], 1)) return false;
		if(checkOverlap(rotationOne[2], 2)) return false;

		if(checkOverlap(rotationTwo[0], 3)) return false;
		if(checkOverlap(rotationTwo[1], 4)) return false;
		if(checkOverlap(rotationTwo[2], 5)) return false;

		// Beste Werte zwischenspeichern, falls es nur noch
		// fast parallele Kanten gibt, die uns keine Aussage
		// machen lassen.
		const unsigned bestSingleAxis = best;


		if(checkOverlap(glm::cross(rotationOne[0], rotationTwo[0]), 6)) return false;
		if(checkOverlap(glm::cross(rotationOne[0], rotationTwo[1]), 7)) return false;
		if(checkOverlap(glm::cross(rotationOne[0], rotationTwo[2]), 8)) return false;
		if(checkOverlap(glm::cross(rotationOne[1], rotationTwo[0]), 9)) return false;
		if(checkOverlap(glm::cross(rotationOne[1], rotationTwo[1]), 10)) return false;
		if(checkOverlap(glm::cross(rotationOne[1], rotationTwo[2]), 11)) return false;
		if(checkOverlap(glm::cross(rotationOne[2], rotationTwo[0]), 12)) return false;
		if(checkOverlap(glm::cross(rotationOne[2], rotationTwo[1]), 13)) return false;
		if(checkOverlap(glm::cross(rotationOne[2], rotationTwo[2]), 14)) return false;

		// Make sure we've got a result.
		assert(best != 0xffffff);

		auto* contact = collisionData.getAvailableEntry();

		// Wir wissen, es gibt eine Kollision und wir wissen, welche der SAT-Achsen
		// die minimale Durchdringung ergab. Nun folgt die Fallunterscheidung:
		if(best < 3)
		{
			// Ecke von Box2 und Fl�che von Box1.
			fillPointFaceBoxBox(box1, box2, toCentre, contact, best, pen);
			return true;
		}
		
		if(best < 6)
		{
			// Ecke von Box1 und Fl�che von Box2.
			// Vertausche Argumente und invertiere toCentre
			fillPointFaceBoxBox(box2, box1, -toCentre, contact, best - 3, pen);
			return true;
		}

		// Im Fall Kante-Kante suche die SAT-Achse:
		best -= 6; // damit nur noch 0..8
		unsigned int oneAxisIndex = best / 3;
		unsigned int twoAxisIndex = best % 3;
		glm::vec3 oneAxis = rotationOne[oneAxisIndex];
		glm::vec3 twoAxis = rotationTwo[twoAxisIndex];
		glm::vec3 axis = glm::cross(oneAxis, twoAxis);
		axis = glm::normalize(axis);

		// Die Achse soll von Box 1 zu Box 2 zeigen.
		if(glm::dot(axis, toCentre) > real(0))
		{
			axis *= real(-1);
		}
		// Wir kennen die Achse, aber nicht, welche Kanten betroffen sind.
		// Dazu suchen wir den Mittelpunkt der Kanten (eine Koordinate der
		// halfSize ist 0) und wir bestimmen die n�chstliegende andere Achse.
		glm::vec3 ptOnOneEdge = box1->getHalfSize();
		glm::vec3 ptOnTwoEdge = box2->getHalfSize();
		for(unsigned int i = 0; i < 3; ++i)
		{
			if(i == oneAxisIndex)
			{
				ptOnOneEdge[i] = real(0);
			}
				// sonst: eine oder andere Kante.
			else if(glm::dot(rotationOne[i], axis) > real(0))
			{
				ptOnOneEdge[i] = -ptOnOneEdge[i];
			}

			if(i == twoAxisIndex)
			{
				ptOnTwoEdge[i] = real(0);
			}
				// sonst: eine oder andere Kante.
			else if(glm::dot(rotationTwo[i], axis) < real(0))
			{
				ptOnTwoEdge[i] = -ptOnTwoEdge[i];
			}
		}

		//////////////////////////////////////////////////////////////////////////

		// Transformation in Weltkoordinaten:
		ptOnOneEdge = rbBox1->getTransform().getPointInWorldSpace(ptOnOneEdge);
		ptOnTwoEdge = rbBox2->getTransform().getPointInWorldSpace(ptOnTwoEdge);

		// Wir haben jetzt einen Punkt und eine Richtung f�r die kollidierenden
		// Kanten. Wir suchen jetzt den Punkt wo die beiden Kanten am n�chsten
		// zusammeniegen.
		const glm::vec3 vertex = contactPoint(
			ptOnOneEdge, oneAxis, box1->getHalfSize()[oneAxisIndex],
			ptOnTwoEdge, twoAxis, box2->getHalfSize()[twoAxisIndex],
			bestSingleAxis > 2);

		// We can fill the contact.
		
		contact->setPenetration(pen);
		contact->setContactNormal(axis);
		contact->setContactPoint(vertex);
		contact->setBodyData(rbBox1, rbBox2);
		return true;
	}

	real BoxBoxNarrowAlgorithm::transformToAxis(const CollisionBox* box,
												const glm::vec3& axis)
	{
		const auto& rotation = box->getBody()->getTransform().getRotationMat();

		return
			box->getHalfSize().x * abs(glm::dot(axis, rotation[0])) +
			box->getHalfSize().y * abs(glm::dot(axis, rotation[1])) +
			box->getHalfSize().z * abs(glm::dot(axis, rotation[2]));
	}

	real BoxBoxNarrowAlgorithm::penetrationOnAxis(const CollisionBox* one,
												  const CollisionBox* two,
												  const glm::vec3& axis,
												  const glm::vec3& toCentre)
	{
		// Projektionen der halfSizes auf die Achse:
		const real oneProject = transformToAxis(one, axis);
		const real twoProject = transformToAxis(two, axis);

		// Projektion des Abstandsvektors auf die Achse.
		const real distance = abs(glm::dot(toCentre, axis));

		// R�ckgabe der �berlappung. Positive Werte
		// bedeuten �berlappung, negative keine.
		return oneProject + twoProject - distance;
	}

	bool BoxBoxNarrowAlgorithm::tryAxis(const CollisionBox* one,
										const CollisionBox* two,
										glm::vec3 axis,
										const glm::vec3& toCentre,
	                                    const unsigned index,
										real& smallestPenetration, 
										unsigned& smallestCase)
	{
		// Fast parallele Achsen nicht ber�cksichtigen.
		if(real(glm::length2(axis)) < s_epsilon)
		{
			return true;
		}
		axis = glm::normalize(axis);

		const real penetration = penetrationOnAxis(one, two, axis, toCentre);

		if(penetration < 0)
		{
			return false;
		}
		if(penetration < smallestPenetration)
		{
			smallestPenetration = penetration;
			smallestCase = index;
		}
		return true;
	}

	void BoxBoxNarrowAlgorithm::fillPointFaceBoxBox(const CollisionBox* box1,
													const CollisionBox* box2,
													const glm::vec3& toCentre,
													Contact* contact,
													const unsigned best,
	                                                const real penetration)
	{
		auto* rbBox1 = box1->getBody();
		auto* rbBox2 = box2->getBody();

		const auto& rotationOne = rbBox1->getTransform().getRotationMat();
		const auto& rotationTwo = rbBox2->getTransform().getRotationMat();

		glm::vec3 normal = rotationOne[best];
		// Richtige Fl�che ausw�hlen:
		if(glm::dot(rotationOne[best], toCentre) > real(0))
		{
			normal = -normal;
		}

		// Welche Ecke der anderen Box ist betroffen? toCentre reicht nicht!
		// Es k�nnten alle 6 Ecken sein, daher 6 Variationen: Zeigt ein Punkt 
		// in die entgegengesetze Richtung negieren wir seine Koordinate, um 
		//eine andere Ecke zu erhalten:
		glm::vec3 vertex = box2->getHalfSize();
		if(glm::dot(rotationTwo[0], normal) < real(0))
		{
			vertex.x = -vertex.x;
		}
		if(glm::dot(rotationTwo[1], normal) < real(0))
		{
			vertex.y = -vertex.y;
		}
		if(glm::dot(rotationTwo[2], normal) < real(0))
		{
			vertex.z = -vertex.z;
		}

		// Create the contact data
		contact->setContactNormal(normal);
		contact->setPenetration(penetration);
		
		contact->setContactPoint(rbBox2->getPointInWorldSpace(vertex));
		contact->setBodyData(rbBox1, rbBox2);
	}

	glm::vec3 BoxBoxNarrowAlgorithm::contactPoint(const glm::vec3& pOne,
												  const glm::vec3& dOne,
	                                              const real oneSize,
												  const glm::vec3& pTwo, 
												  const glm::vec3& dTwo,
	                                              const real twoSize,
	                                              const bool useOne)
	{
		const real smOne = glm::length2(dOne);
		const real smTwo = glm::length2(dTwo);
		const real dpOneTwo = glm::dot(dTwo, dOne);

		const glm::vec3 toSt = pOne - pTwo;
		const real dpStaOne = glm::dot(dOne, toSt);
		const real dpStaTwo = glm::dot(dTwo, toSt);

		const real denom = smOne * smTwo - dpOneTwo * dpOneTwo;

		/** Check if edges are parallel */
		if(real(abs(denom)) < s_epsilon)
		{
			return useOne ? pOne : pTwo;
		}

		const real mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
		const real mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

		// Edge-Face-Contact:
		if(mua > oneSize ||
		   mua < -oneSize ||
		   mub > twoSize ||
		   mub < -twoSize)
		{
			return useOne ? pOne : pTwo;
		}
		
		const glm::vec3 cOne = pOne + (dOne * mua);
		const glm::vec3 cTwo = pTwo + (dTwo * mub);

		return real(0.5) * (cOne + cTwo);
	}
}
