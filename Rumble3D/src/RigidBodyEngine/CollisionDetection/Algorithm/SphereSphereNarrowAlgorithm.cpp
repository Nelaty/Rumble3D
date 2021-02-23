#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/SphereSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"

#include <glm/glm.hpp>

namespace r3
{
	bool SphereSphereNarrowAlgorithm::generateContactDataImpl(RigidBody* rbSphere1, CollisionSphere* sphere1,
															  RigidBody* rbSphere2, CollisionSphere* sphere2,
															  CollisionData& collisionData)
	{
		if(collisionData.isFull()) return false;

		// Sphere positions
		const auto positionOne = rbSphere1->getTransform().getPosition();
		const auto positionTwo = rbSphere2->getTransform().getPosition();

		// Vector and distance between both spheres
		const auto midline = positionOne - positionTwo;
		const auto distance = glm::length(midline);
		const auto combinedSphereSize = sphere1->getRadius() + sphere2->getRadius();

		// Spheres don't overlap
		if(distance <= 0.0f || distance >= combinedSphereSize) return false;

		// Calculate derived data
		const auto normal = midline / distance;
		const real penetration = combinedSphereSize - distance;
		
		// The contact point is right in the middle of the spheres' intersection
		glm::vec3 contactPoint = positionTwo + normal * (sphere2->getRadius() - real(0.5) * penetration);

		// Initialize the new contact
		auto* contact = collisionData.getAvailableContact();
		contact->setContactNormal(normal);
		contact->setContactPoint(contactPoint);
		contact->setPenetration(penetration);
		contact->setBodyData(rbSphere1, rbSphere2);
		return true;
	}
}
