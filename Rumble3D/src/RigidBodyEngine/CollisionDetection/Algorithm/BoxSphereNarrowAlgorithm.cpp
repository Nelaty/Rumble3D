#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/BoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"



#include <glm/gtx/norm.inl>

namespace r3
{
	bool BoxSphereNarrowAlgorithm::generateContactDataImpl(
		RigidBody* rbBox, CollisionBox* box,
		RigidBody* rbSphere, CollisionSphere* sphere, 
		CollisionData& collisionData)
	{
		// Check if there is room for more contacts
		if(collisionData.getContactsLeft() <= 0)
		{
			return false;
		}

		// Transform the sphere center to box-coordinates
		glm::vec3 center = rbSphere->getTransform().getPosition();
		const auto& boxTransform = rbBox->getTransform();
		glm::vec3 relCenter = glm::transpose(boxTransform.getRotationMat()) *
			(center - boxTransform.getPosition());

		// Early out check 
		const auto& boxDim = box->getHalfSize();
		const auto radius = sphere->getRadius();
		if(abs(relCenter.x) - radius > boxDim.x ||
		   abs(relCenter.y) - radius > boxDim.y ||
		   abs(relCenter.z) - radius > boxDim.z)
		{
			return false;
		}

		// Clamp each coordinate to the box.
		glm::vec3 closestPt{};
		closestPt.x = glm::clamp(relCenter.x, -boxDim.x, boxDim.x);
		closestPt.y = glm::clamp(relCenter.y, -boxDim.y, boxDim.y);
		closestPt.z = glm::clamp(relCenter.z, -boxDim.z, boxDim.z);
		
		// Check if there is a contact
		const auto distance = glm::length2(closestPt - relCenter);
		if(distance > radius * radius)
		{
			return false;
		}

		// Create the contact
		const auto closestPtWorld = rbBox->getPointInWorldSpace(closestPt);
		
		auto* contact = collisionData.getAvailableContact();
		glm::vec3 contactNormal = glm::normalize(closestPtWorld - center);
		contact->setContactNormal(contactNormal);
		contact->setContactPoint(closestPtWorld);
		contact->setPenetration(sphere->getRadius() - sqrt(distance));
		contact->setBodyData(rbBox, rbSphere);
		return true;
	}
}
