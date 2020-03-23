#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/PlaneSphereCollisionAlgorithm.h"

#include <glm/gtx/norm.inl>

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

		// Cache the sphere position
		const auto& position = rbSphere->getTransform().getPosition();

		// Find the distance from the plane
		real ballDistance =
			glm::dot(plane->getNormal(), position) -
			sphere->getRadius() - plane->getOffset();

		// If sphere doesn't collide with plane, it will also not
		// collide with a finite one
		if(ballDistance >= 0) return false;

		if(plane->isHalfSpace())
		{
			// Create the contact - it has a normal in the plane direction.
			Contact* contact = collisionData.getAvailableContact();
			contact->setContactNormal(plane->getNormal());
			contact->setPenetration(-ballDistance);
			contact->setContactPoint(position - plane->getNormal() * (ballDistance + sphere->getRadius()));
			contact->setBodyData(rbSphere, rbPlane);

			return true;
		}


		const auto& planeTransform = rbPlane->getTransform();
		const auto& planeDim = plane->getHalfSizes();
		const auto radius = sphere->getRadius();

		glm::vec3 relCenter = glm::transpose(planeTransform.getRotationMat()) *
			(position - planeTransform.getPosition());

		// Clamp each coordinate to the box.
		glm::vec3 closestPt{};
		closestPt.x = glm::clamp(relCenter.x, -planeDim.x, planeDim.x);
		closestPt.y = ballDistance;
		closestPt.z = glm::clamp(relCenter.z, -planeDim.y, planeDim.y);

		// Check if there is a contact
		const auto distance = glm::length2(closestPt - relCenter);
		if(distance > radius * radius)
		{
			return false;
		}

		// Create the contact
		auto closestPtWorld = rbPlane->getPointInWorldSpace(closestPt);
		closestPtWorld.z *= -1; // hacky

		auto* contact = collisionData.getAvailableContact();
		glm::vec3 contactNormal = glm::normalize(closestPtWorld - position);
		contact->setContactNormal(contactNormal);
		contact->setContactPoint(closestPtWorld);
		contact->setPenetration(sphere->getRadius() - sqrt(distance));
		contact->setBodyData(rbPlane, rbSphere);
		return true;
	}
}
