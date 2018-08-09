#include "R3D/RigidBodyEngine/CollisionDetector.h"

#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace rum
{
	unsigned CollisionDetector::sphereAndHalfSpace(
		const CollisionSphere &sphere,
		const CollisionPlane &plane,
		CollisionData *data)
	{
		// Make sure we have contacts
		if(data->getContactsLeft() <= 0)
		{
			return 0;
		}

		// Cache the sphere position
		glm::vec3 position = sphere.GetAxis(3);
	
		// Find the distance from the plane
		real ballDistance =	glm::dot(plane.GetNormal(), position) -
			sphere.GetRadius() - plane.GetOffset();
	
		if(ballDistance >= 0)
		{
			return 0;
		}
		// Create the contact - it has a normal in the plane direction.
		Contact* contact = data->getContacts();
		contact->SetContactNormal(plane.GetNormal());
		contact->SetPenetration(-ballDistance);
		contact->SetContactPoint(position - plane.GetNormal() * (ballDistance + sphere.GetRadius()));
		contact->SetBodyData(sphere.GetBody(), nullptr, data->getFriction(), data->getRestitution());
	
		data->addContacts(1);
		return 1;
	}
	
	unsigned CollisionDetector::sphereAndTruePlane(const CollisionSphere &sphere,
												   const CollisionPlane &plane,
												   CollisionData *data)
	{ // Implementierung entfällt, da hier nicht benötigt.
		return 1;
	}
	
	unsigned CollisionDetector::sphereAndSphere(const CollisionSphere &one, 
												const CollisionSphere &two, 
												CollisionData *data)
	{
		// Wenn Kontakt-Array voll ist, nichts mehr zu tun:
		if(data->getContactsLeft() <= 0)
		{
			return 0;
		}

		// Positionen der Kugeln:
		glm::vec3 positionOne = one.GetAxis(3);
		glm::vec3 positionTwo = two.GetAxis(3);
	
		// Vector zwischen den Kugeln und seine Länge:
		glm::vec3 midline = positionOne - positionTwo;
		real size = glm::length(midline);
	
		// Keine Kollision:
		if (size <= 0.0f || size >= one.GetRadius() + two.GetRadius())
		{
			return 0;
		}
	
		// Erstellung der Kontaktnormalen und der Kontaktdaten:
		glm::vec3 normal = midline * (static_cast<real>(1.0f) / size);
		Contact* contact = data->getContacts();
		contact->SetContactNormal(normal);
		contact->SetContactPoint(positionOne + midline * static_cast<real>(0.5f));
		contact->SetPenetration((one.GetRadius() + two.GetRadius() - size));
		contact->SetBodyData(one.GetBody(), two.GetBody(),
							 data->getFriction(), data->getRestitution());
		
		data->addContacts(1);
		return 1;
	}
	
	unsigned CollisionDetector::boxAndHalfSpace(const CollisionBox &box,
												const CollisionPlane &plane,
												CollisionData *data)
	{
		// Make sure we have contacts
		if(data->getContactsLeft() <= 0)
		{
			return 0;
		}

		/*
		// Check for intersection
		if (!IntersectionTests::boxAndHalfSpace(box, plane))
		{
			return 0;
		}
		*/
	
		// We have an intersection, so find the intersection points. We can make
		// do with only checking vertices. If the box is resting on a plane
		// or on an edge, it will be reported as four or two contact points.
	
		// Go through each combination of + and - for each half-size
		static constexpr real mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 },
		{ 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };
	
		Contact* contact = data->getContacts();
		unsigned contactsUsed = 0;
		for (unsigned i = 0; i < 8; i++) {
	
			// Calculate the position of each vertex
			glm::vec3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
			vertexPos *= box.getHalfSize();
			vertexPos = glm::vec3(box.GetTransform() * glm::vec4(vertexPos, static_cast<real>(1.0f)));

			// Abstand von der Ebene:
			real vertexDistance = glm::dot(vertexPos, plane.GetNormal());
	
			// Vergleich mit dem Abstand der EBene vomUrsprung:
			if (vertexDistance <= plane.GetOffset())
			{
				// Create the contact data.
				// The contact point is halfway between the vertex and the
				// plane - we multiply the direction by half (?) the separation
				// distance and add the vertex location.
				glm::vec3 tmp = plane.GetNormal();
				tmp *= (vertexDistance - plane.GetOffset());
				tmp += vertexPos;
				contact->SetContactPoint(tmp);
				contact->SetContactNormal(plane.GetNormal());
				contact->SetPenetration(plane.GetOffset() - vertexDistance);
				contact->SetBodyData(box.GetBody(), nullptr,
					data->getFriction(), data->getRestitution());
	
				// Verwaltung der Indizes des Arrays
				++contact;
				++contactsUsed;
				if(contactsUsed == (unsigned)data->getContactsLeft())
				{
					return contactsUsed;
				}
			}
		}
	
		data->addContacts(contactsUsed);
		return contactsUsed;
	}
	
	/*
	unsigned CollisionDetector::boxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane,
		CollisionData *data ){
		// Haben wir noch Platz im Kontakt-Array
		if (data->getContactsLeft() <= 0) return 0;
	
		 // Check for intersection
		if (!IntersectionTests::boxAndHalfSpace(box, plane))
		{ return 0; }
	
		// Es kommt zu einemKontakt. Also berechnen wir die max. 4 Kontaktpunkte:
		// Alle Kombinationen der Ecken über die halfSize:
		static real mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 },
		{ 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };
	
		Contact* contact = data->getContacts();
		unsigned contactsUsed = 0;
		for (unsigned i = 0; i < 8; i++) {
	
			// Calculate the position of each vertex
			glm::vec3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
			vertexPos.componentProductUpdate(box.getHalfSize());
			vertexPos = box.getTransform().transform(vertexPos);
	
	
	
		}
	
		data->addContacts(contactsUsed);
		return contactsUsed;
	}
	
	*/
	
	unsigned CollisionDetector::boxAndSphere(const CollisionBox &box,
											 const CollisionSphere &sphere,
											 CollisionData *data)
	{
		// Kugelmittelpunkt in Quaderkoordinaten transformieren:
		glm::vec3 centre = sphere.GetAxis(3);
		//glm::vec3 relCentre = box.GetTransform().transformInverse(centre);
		// TODO: test result
		glm::vec3 relCentre = glm::transpose(glm::mat3(box.GetTransform())) * 
			(centre - glm::vec3(box.GetTransform()[3]));
		
		real boxX = box.getHalfSize().x;
		real boxY = box.getHalfSize().y;
		real boxZ = box.getHalfSize().z;
	
		// Early out check 
		if (abs(relCentre.x) - sphere.GetRadius() > boxX ||
			abs(relCentre.y) - sphere.GetRadius() > boxY ||
			abs(relCentre.z) - sphere.GetRadius() > boxZ)
		{
			return 0;
		}
	
		glm::vec3 closestPt(0, 0, 0);
		real dist;
	
		// Clamp each coordinate to the box.
		dist = relCentre.x;
		dist = glm::clamp(dist, -boxX, boxX);
		closestPt.x = dist;
	
		dist = relCentre.y;
		dist = glm::clamp(dist, -boxY, boxY);
		closestPt.y = dist;
	
		dist = relCentre.z;
		dist = glm::clamp(dist, -boxZ, boxZ);
		closestPt.z = dist;
	
		// Prüfe, ob ein Kontakt vorliegt:
		dist = glm::length2(closestPt - relCentre);
		if(dist > sphere.GetRadius() * sphere.GetRadius())
		{
			return 0;
		}

		// Erstelle den Kontakt:
		glm::vec3 closestPtWorld = 
			glm::vec3(box.GetTransform() * glm::vec4(closestPt, static_cast<real>(1.0f)));
	
		Contact* contact = data->getContacts();
		glm::vec3 tmp = (closestPtWorld - centre);
		tmp = glm::normalize(tmp);
		contact->SetContactNormal(tmp);
		contact->SetContactPoint(closestPtWorld);
		contact->SetPenetration(sphere.GetRadius() - sqrt(dist));
		contact->SetBodyData(box.GetBody(), sphere.GetBody(),
			data->getFriction(), data->getRestitution());
	
		data->addContacts(1);
		return 1;
	} // Ende CollisionDetector::boxAndSphere
	
	real CollisionDetector::transformToAxis(const CollisionBox &box,
											const glm::vec3 &axis)
	{
		return
			box.getHalfSize().x * abs(glm::dot(axis, box.GetAxis(0))) +
			box.getHalfSize().y * abs(glm::dot(axis, box.GetAxis(1))) +
			box.getHalfSize().z * abs(glm::dot(axis, box.GetAxis(2)));
	}
	
	real CollisionDetector::penetrationOnAxis(const CollisionBox &one,
											  const CollisionBox &two,
											  const glm::vec3 &axis,
											  const glm::vec3 &toCentre)
	{
		// Projektionen der halfSizes auf die Achse:
		real oneProject = transformToAxis(one, axis);
		real twoProject = transformToAxis(two, axis);
	
		// Projektion des Abstandsvektors auf die Achse.
		real distance = abs(glm::dot(toCentre, axis));
	
		// Rückgabe der Überlappung. Positive Werte
		// bedeuten Überlappung, negative keine.
		return oneProject + twoProject - distance;
	}
	
	bool CollisionDetector::tryAxis(const CollisionBox &one,
									const CollisionBox &two,
									glm::vec3 axis,
									const glm::vec3& toCentre,
									unsigned index,
									// INOUT Parameter
									real& smallestPenetration,
									unsigned &smallestCase)
	{
		// Fast parallele Achsen nicht berücksichtigen.
		if(glm::length2(axis) < 0.0001)
		{
			return true;
		}
		axis = glm::normalize(axis);
	
		real penetration = penetrationOnAxis(one, two, axis, toCentre);
	
		if(penetration < 0)
		{
			return false;
		}
		if (penetration < smallestPenetration) 
		{
			smallestPenetration = penetration;
			smallestCase = index;
		}
		return true;
	}
	
	// This preprocessor definition is only used as a convenience
	// in the boxAndBox contact generation method.
	#define CHECK_OVERLAP(axis, index) \
	if (!tryAxis(one, two, (axis), toCentre, (index), pen, best)) return 0;
	
	unsigned CollisionDetector::boxAndBox(const CollisionBox &one,
										  const CollisionBox &two,
										  CollisionData *data)
	{
		// Vektor zwischen den Schwerpunkten:
		glm::vec3 twoCentre = two.GetAxis(3);
		glm::vec3 oneCentre = one.GetAxis(3);
		glm::vec3 toCentre(0, 0, 0);
		toCentre = twoCentre - oneCentre;
		// Angenommen,es gibt keinen Kontakt:
		real pen = EROS_REAL_MAX;
		unsigned int best = 0xffffff;
	
		// SAT-Test mit allen Achsen. Wenn ein Test positiv ist,
		// verlassen wir die Methode mit 0Kontakten.
		// Sonst suchen wir die Achsemit der minimalen Durchdringung:
		CHECK_OVERLAP(one.GetAxis(0), 0);
		CHECK_OVERLAP(one.GetAxis(1), 1);
		CHECK_OVERLAP(one.GetAxis(2), 2);
	
		CHECK_OVERLAP(two.GetAxis(0), 3);
		CHECK_OVERLAP(two.GetAxis(1), 4);
		CHECK_OVERLAP(two.GetAxis(2), 5);
	
		// Beste Werte zwischenspeichern, falls es nur noch
		// fast parallele Kanten gibt, die uns keine Aussage
		// machen lassen.
		unsigned int bestSingleAxis = best;
			
		CHECK_OVERLAP(glm::cross(one.GetAxis(0), two.GetAxis(0)), 6);
		CHECK_OVERLAP(glm::cross(one.GetAxis(0), two.GetAxis(1)), 7);
		CHECK_OVERLAP(glm::cross(one.GetAxis(0), two.GetAxis(2)), 8);
		CHECK_OVERLAP(glm::cross(one.GetAxis(1), two.GetAxis(0)), 9);
		CHECK_OVERLAP(glm::cross(one.GetAxis(1), two.GetAxis(1)), 10);
		CHECK_OVERLAP(glm::cross(one.GetAxis(1), two.GetAxis(2)), 11);
		CHECK_OVERLAP(glm::cross(one.GetAxis(2), two.GetAxis(0)), 12);
		CHECK_OVERLAP(glm::cross(one.GetAxis(2), two.GetAxis(1)), 13);
		CHECK_OVERLAP(glm::cross(one.GetAxis(2), two.GetAxis(2)), 14);

		// Make sure we've got a result.
		// assert(best != 0xffffff);
	
		// Wir wissen, es gibt eine Kollision und wir wissen, welche der SAT-Achsen
		// die minimale Durchdringung ergab. Nun folgt die Fallunterscheidung:
		if (best < 3)
		{
			// Ecke von Box2 und Fläche von Box1.
			fillPointFaceBoxBox(one, two, toCentre, data, best, pen);
			data->addContacts(1);
			return 1;
		}
		else if (best < 6)
		{
			// Ecke von Box1 und Fläche von Box2.
			// Vertausche Argumente und invertiere toCentre
			fillPointFaceBoxBox(two, one, toCentre*-1.0f, data, best - 3, pen);
			data->addContacts(1);
			return 1;
		}
		else
		{
			// Im Fall Kante-Kante suche die SAT-Achse:
			best -= 6; // damit nur noch 0..8
			unsigned int oneAxisIndex = best / 3;
			unsigned int twoAxisIndex = best % 3;
			glm::vec3 oneAxis = one.GetAxis(oneAxisIndex);
			glm::vec3 twoAxis = two.GetAxis(twoAxisIndex);
			glm::vec3 axis = glm::cross(oneAxis, twoAxis);
			axis = glm::normalize(axis);
	
			// Die Achse soll von Box 1 zu Box 2 zeigen.
			if(glm::dot(axis, toCentre) > static_cast<real>(0.0f))
			{
				axis *= static_cast<real>(1.0f);
			}
			// Wir kennen die Achse, aber nicht, welche Kanten betroffen sind.
			// Dazu suchen wir den Mittelpunkt der Kanten (eine Koordinate der
			// halfSize ist 0) und wir bestimmen die nächstliegende andere Achse.
			glm::vec3 ptOnOneEdge = one.getHalfSize();
			glm::vec3 ptOnTwoEdge = two.getHalfSize();
			for (int i = 0; i < 3; ++i)
			{
				if (i == oneAxisIndex) 
				{
					ptOnOneEdge[i] = static_cast<real>(0.0f);
				}
				// sonst: eine oder andere Kante.
				else if (glm::dot(one.GetAxis(i), axis) > static_cast<real>(0.0f)) 
				{
					ptOnOneEdge[i] = -(ptOnOneEdge[i]);
				}
	
				if (i == twoAxisIndex) 
				{
					ptOnTwoEdge[i] = static_cast<real>(0.0f);
				}
				// sonst: eine oder andere Kante.
				else if (glm::dot(two.GetAxis(i), axis) < static_cast<real>(0.0f)) 
				{
					ptOnTwoEdge[i] = -(ptOnTwoEdge[i]);
				}
			}
			

			//////////////////////////////////////////////////////////////////////////
	
			// Transformation in Weltkoordinaten:
			ptOnOneEdge = glm::vec3(one.GetTransform() * glm::vec4(ptOnOneEdge, static_cast<real>(1.0f)));
			ptOnTwoEdge = glm::vec3(two.GetTransform() * glm::vec4(ptOnTwoEdge, static_cast<real>(1.0f)));
	
			// Wir haben jetzt einen Punkt und eine Richtung für die kollidierenden
			// Kanten. Wir suchen jetzt den Punkt wo die beiden Kanten am nächsten
			// zusammeniegen.
			glm::vec3 vertex = contactPoint(
				ptOnOneEdge, oneAxis, one.getHalfSize()[oneAxisIndex],
				ptOnTwoEdge, twoAxis, two.getHalfSize()[twoAxisIndex],
				bestSingleAxis > 2);
	
			// We can fill the contact.
			Contact* contact = data->getContacts();
	
			contact->SetPenetration(pen);
			contact->SetContactNormal(axis);
			contact->SetContactPoint(vertex);
			contact->SetBodyData(one.GetBody(), two.GetBody(),
								 data->getFriction(), data->getRestitution());
			data->addContacts(1);
			return 1;
		}
		return 0;
		
	}
	
	void CollisionDetector::fillPointFaceBoxBox(const CollisionBox &one,
												const CollisionBox &two,
												const glm::vec3 &toCentre,
												CollisionData *data,
												unsigned best,
												real pen)
	{
		Contact* contact = data->getContacts();
		glm::vec3 normal = one.GetAxis(best);
		// Richtige Fläche auswählen:
		if (glm::dot(one.GetAxis(best), toCentre) >  static_cast<real>(0.0f))
		{
			normal = -normal;
		}

		// Welche Ecke der anderen Box ist betroffen? toCentre reicht nicht!
		// Es könnten alle 6 Ecken sein, daher 6 Variationen: Zeigt ein Punkt 
		// in die entgegengesetze Richtung negieren wir seine Koordinate, um 
		//eine andere Ecke zu erhalten:
		glm::vec3 vertex = two.getHalfSize();
		if(glm::dot(two.GetAxis(0), normal) < static_cast<real>(0.0f))
		{
			vertex.x = -vertex.x;
		}
		if(glm::dot(two.GetAxis(1), normal) < static_cast<real>(0.0f))
		{
			vertex.y = -vertex.y;
		}
		if(glm::dot(two.GetAxis(2), normal) < static_cast<real>(0.0f))
		{
			vertex.z = -vertex.z;
		}

		// Create the contact data
		contact->SetContactNormal(normal);
		contact->SetPenetration(pen);
		contact->SetContactPoint(glm::vec3(two.GetTransform() * glm::vec4(vertex, static_cast<real>(1.0f))));
		contact->SetBodyData(one.GetBody(), two.GetBody(),
			data->getFriction(), data->getRestitution());
	}
	
	glm::vec3 CollisionDetector::contactPoint(const glm::vec3 &pOne,
											  const glm::vec3 &dOne,
											  real oneSize,
											  const glm::vec3 &pTwo,
											  const glm::vec3 &dTwo,
											  real twoSize,
											  bool useOne)
	{
		glm::vec3 toSt, cOne, cTwo;
		real dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
		real denom, mua, mub;
	
		smOne = glm::length2(dOne);
		smTwo = glm::length2(dTwo);
		dpOneTwo = glm::dot(dTwo, dOne);

		toSt = pOne - pTwo;
		dpStaOne = glm::dot(dOne, toSt);
		dpStaTwo = glm::dot(dTwo, toSt);
	
		denom = smOne * smTwo - dpOneTwo * dpOneTwo;
	
		// Nenner 0 bedeutet parallele Kanten:
		if (abs(denom) < 0.0001f) 
		{
			return useOne ? pOne : pTwo;
		}
	
		mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
		mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;
	
		// Kante-Fläche-Kontakt:
		if (mua > oneSize ||
			mua < -oneSize ||
			mub > twoSize ||
			mub < -twoSize)
		{
			return useOne ? pOne : pTwo;
		}
		else
		{
			cOne = pOne + (dOne * mua);
			cTwo = pTwo + (dTwo * mub);
	
			return static_cast<real>(0.5f) * (cOne + cTwo);
		}
	}
}