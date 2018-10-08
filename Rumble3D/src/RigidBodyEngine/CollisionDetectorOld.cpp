#include "R3D/RigidBodyEngine/CollisionDetectorOld.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace r3
{
	unsigned CollisionDetectorOld::sphereAndHalfSpace(
		const CollisionSphere &sphere,
		const CollisionPlane &plane,
		CollisionDataOld *data)
	{
		// Make sure we have contacts
		if(data->getContactsLeft() <= 0)
		{
			return 0;
		}

		// Cache the sphere position
		const auto position = sphere.getAxis(3);
	
		// Find the distance from the plane
		const auto ballDistance =	glm::dot(plane.getNormal(), position) -
			sphere.getRadius() - plane.getOffset();
	
		if(ballDistance >= 0)
		{
			return 0;
		}
		// Create the contact - it has a normal in the plane direction.
		auto contact = data->getContacts();
		contact->setContactNormal(plane.getNormal());
		contact->setPenetration(-ballDistance);
		contact->setContactPoint(position - plane.getNormal() * (ballDistance + sphere.getRadius()));
		contact->setBodyData(sphere.getBody(), nullptr, data->getFriction(), data->getRestitution());
	
		data->addContacts(1);
		return 1;
	}
	
	unsigned CollisionDetectorOld::sphereAndTruePlane(const CollisionSphere &sphere,
												   const CollisionPlane &plane,
													  CollisionDataOld *data)
	{ // Implementierung entfällt, da hier nicht benötigt.
		return 1;
	}
	
	unsigned CollisionDetectorOld::boxAndHalfSpace(const CollisionBox &box,
												   const CollisionPlane &plane,
												   CollisionDataOld *data)
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
	
		ContactOld* contact = data->getContacts();
		unsigned contactsUsed = 0;
		for (unsigned i = 0; i < 8; i++) {
	
			// Calculate the position of each vertex
			glm::vec3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
			vertexPos *= box.getHalfSize();
			vertexPos = glm::vec3(box.getTransform() * glm::vec4(vertexPos, static_cast<real>(1.0f)));

			// Abstand von der Ebene:
			real vertexDistance = glm::dot(vertexPos, plane.getNormal());
	
			// Vergleich mit dem Abstand der EBene vomUrsprung:
			if (vertexDistance <= plane.getOffset())
			{
				// Create the contact data.
				// The contact point is halfway between the vertex and the
				// plane - we multiply the direction by half (?) the separation
				// distance and RegisterForce the vertex location.
				glm::vec3 tmp = plane.getNormal();
				tmp *= (vertexDistance - plane.getOffset());
				tmp += vertexPos;
				contact->setContactPoint(tmp);
				contact->setContactNormal(plane.getNormal());
				contact->setPenetration(plane.getOffset() - vertexDistance);
				contact->setBodyData(box.getBody(), nullptr,
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
	
	real CollisionDetectorOld::transformToAxis(const CollisionBox &box,
											const glm::vec3 &axis)
	{
		return
			box.getHalfSize().x * abs(glm::dot(axis, box.getAxis(0))) +
			box.getHalfSize().y * abs(glm::dot(axis, box.getAxis(1))) +
			box.getHalfSize().z * abs(glm::dot(axis, box.getAxis(2)));
	}
	
	real CollisionDetectorOld::penetrationOnAxis(const CollisionBox &one,
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
	
	bool CollisionDetectorOld::tryAxis(const CollisionBox &one,
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
	
	void CollisionDetectorOld::fillPointFaceBoxBox(const CollisionBox &one,
												   const CollisionBox &two,
												   const glm::vec3 &toCentre,
												   CollisionDataOld *data,
	                                               const unsigned best,
	                                               const real pen)
	{
		ContactOld* contact = data->getContacts();
		glm::vec3 normal = one.getAxis(best);
		// Richtige Fläche auswählen:
		if (glm::dot(one.getAxis(best), toCentre) >  static_cast<real>(0.0f))
		{
			normal = -normal;
		}

		// Welche Ecke der anderen Box ist betroffen? toCentre reicht nicht!
		// Es könnten alle 6 Ecken sein, daher 6 Variationen: Zeigt ein Punkt 
		// in die entgegengesetze Richtung negieren wir seine Koordinate, um 
		//eine andere Ecke zu erhalten:
		glm::vec3 vertex = two.getHalfSize();
		if(glm::dot(two.getAxis(0), normal) < static_cast<real>(0.0f))
		{
			vertex.x = -vertex.x;
		}
		if(glm::dot(two.getAxis(1), normal) < static_cast<real>(0.0f))
		{
			vertex.y = -vertex.y;
		}
		if(glm::dot(two.getAxis(2), normal) < static_cast<real>(0.0f))
		{
			vertex.z = -vertex.z;
		}

		// Create the contact data
		contact->setContactNormal(normal);
		contact->setPenetration(pen);
		contact->setContactPoint(glm::vec3(two.getTransform() * glm::vec4(vertex, static_cast<real>(1.0f))));
		contact->setBodyData(one.getBody(), two.getBody(),
			data->getFriction(), data->getRestitution());
	}
	
	glm::vec3 CollisionDetectorOld::contactPoint(const glm::vec3 &pOne,
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