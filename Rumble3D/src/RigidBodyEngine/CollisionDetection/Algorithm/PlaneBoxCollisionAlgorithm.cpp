#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlaneBoxCollisionAlgorithm.h"

#include <glm/glm.hpp>

namespace r3
{
	PlaneBoxCollisionAlgorithm::PlaneBoxCollisionAlgorithm()
	= default;

	PlaneBoxCollisionAlgorithm::~PlaneBoxCollisionAlgorithm()
	= default;

	bool PlaneBoxCollisionAlgorithm::generateContactDataImpl(RigidBody* rbPlane, 
															 CollisionPlane* plane,
															 RigidBody* rbBox,
															 CollisionBox* box,
															 CollisionData& collisionData)
	{
		if (collisionData.isFull())
		{
			return false;
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
		static constexpr real mults[8][3] = 
		{
			{ 1, 1, 1 },{ -1, 1, 1 },{ 1, -1, 1 },{ -1, -1, 1 },
			{ 1, 1, -1 },{ -1, 1, -1 },{ 1, -1, -1 },{ -1, -1, -1 }
		};

		if(plane->isHalfSpace())
		{
			for (unsigned i = 0; i < 8; i++) {

				// Calculate the position of each vertex
				glm::vec3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
				vertexPos *= box->getHalfSize();
				vertexPos = glm::vec3(box->getTransform() * glm::vec4(vertexPos, static_cast<real>(1.0f)));

				// Abstand von der Ebene:
				real vertexDistance = glm::dot(vertexPos, plane->getNormal());

				// Vergleich mit dem Abstand der EBene vomUrsprung:
				if (vertexDistance <= plane->getOffset())
				{
					if (collisionData.isFull())
					{
						return false;
					}

					auto* contact = collisionData.getAvailableContact();

					// Create the contact data.
					// The contact point is halfway between the vertex and the
					// plane - we multiply the direction by half (?) the separation
					// distance and RegisterForce the vertex location.
					glm::vec3 tmp = plane->getNormal();
					tmp *= (vertexDistance - plane->getOffset());
					tmp += vertexPos;
					contact->setContactPoint(tmp);
					contact->setContactNormal(plane->getNormal());
					contact->setPenetration(plane->getOffset() - vertexDistance);
					contact->setBodyData(rbBox, rbPlane);
				}
			}
		}

		/// \todo: implement when plan is not a half space
		return false;
	}
}
