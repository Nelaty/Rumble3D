#include "R3D/RigidBodyEngine/CollisionDetection/Algorithm/BoxSphereNarrowAlgorithm.h"
#include "R3D/RigidBodyEngine/CollisionBox.h"
#include "R3D/RigidBodyEngine/CollisionSphere.h"



#include <glm/gtx/norm.inl>

namespace r3
{
	BoxSphereNarrowAlgorithm::BoxSphereNarrowAlgorithm()
	= default;

	BoxSphereNarrowAlgorithm::~BoxSphereNarrowAlgorithm()
	= default;

	bool BoxSphereNarrowAlgorithm::generateContactDataImpl(
		RigidBody* rbBox, CollisionBox* box,
		RigidBody* rbSphere, CollisionSphere* sphere, 
		CollisionData& collisionData)
	{
		// Wenn Kontakt-Array voll ist, nichts mehr zu tun:
		if(collisionData.getContactsLeft() <= 0)
		{
			return false;
		}

		// Kugelmittelpunkt in Quaderkoordinaten transformieren:
		glm::vec3 centre = rbSphere->getTransform().getPosition();
		//glm::vec3 relCentre = rbBox->getTransform().transformInverse(centre);
		// TODO: test result
		const auto& boxTransform = rbBox->getTransform();
		glm::vec3 relCentre = glm::transpose(boxTransform.getRotation()) *
			(centre - boxTransform.getPosition());

		// Early out check 
		const auto& boxDim = box->getHalfSize();
		const auto radius = sphere->getRadius();
		if(abs(relCentre.x) - radius > boxDim.x ||
		   abs(relCentre.y) - radius > boxDim.y ||
		   abs(relCentre.z) - radius > boxDim.z)
		{
			return false;
		}

		// Clamp each coordinate to the box.
		glm::vec3 closestPt{};
		closestPt.x = glm::clamp(relCentre.x, -boxDim.x, boxDim.x);
		closestPt.y = glm::clamp(relCentre.y, -boxDim.y, boxDim.y);
		closestPt.z = glm::clamp(relCentre.z, -boxDim.z, boxDim.z);
		
		// Prüfe, ob ein Kontakt vorliegt:
		const auto distance = glm::length2(closestPt - relCentre);
		if(distance > radius * radius)
		{
			return false;
		}

		// Erstelle den Kontakt:
		//glm::vec3 closestPtWorld = 
		//	glm::vec3(box.getTransform() * glm::vec4(closestPt, static_cast<real>(1.0f)));

		const auto closestPtWorld = rbBox->getPointInWorldSpace(closestPt);
		//glm::vec3 closestPtWorld = box->getTransform() * glm::vec4(closestPt, 1);

		auto* contact = collisionData.getAvailableContact();
		glm::vec3 tmp = glm::normalize(closestPtWorld - centre);
		contact->setContactNormal(tmp);
		contact->setContactPoint(closestPtWorld);
		contact->setPenetration(sphere->getRadius() - sqrt(distance));
		contact->setBodyData(rbBox, rbSphere,
							 collisionData.getFriction(), collisionData.getRestitution());
		return true;
	}
}
