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
		// Make sure we have contacts
		if(collisionData.isFull()) return false;

		if(plane->isHalfSpace())
		{
			// Cache the sphere position
			const auto& position = rbSphere->getTransform().getPosition();

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
