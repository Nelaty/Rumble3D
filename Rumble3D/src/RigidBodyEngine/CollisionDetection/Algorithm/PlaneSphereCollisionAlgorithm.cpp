#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlaneSphereCollisionAlgorithm.h"

namespace r3
{
	PlaneSphereCollisionAlgorithm::PlaneSphereCollisionAlgorithm()
	= default;

	PlaneSphereCollisionAlgorithm::~PlaneSphereCollisionAlgorithm()
	= default;

	bool PlaneSphereCollisionAlgorithm::generateContactDataImpl(RigidBody* rbPlane,
																CollisionPlane* plane,
																RigidBody* rbSphere,
																CollisionSphere* sphere,
																CollisionData& collisionData)
	{
		if(plane->isHalfSpace())
		{
			// Make sure we have contacts
			if(collisionData.isFull()) return false;

			// Cache the sphere position
			const auto& position = rbPlane->getTransform().getPosition();

			// Find the distance from the plane
			real ballDistance =
				glm::dot(plane->getNormal(), position) -
				sphere->getRadius() - plane->getOffset();

			if(ballDistance >= 0) return false;

			// Create the contact - it has a normal in the plane direction.
			Contact* contact = collisionData.getAvailableContact();
			contact->setContactNormal(plane->getNormal());
			contact->setPenetration(-ballDistance);
			contact->setContactPoint(position - plane->getNormal() * (ballDistance + sphere->getRadius()));
			contact->setBodyData(rbSphere, rbPlane);

			return true;
		}


		/// \todo: implement -> plane is not half space
		return false;
	}
}
