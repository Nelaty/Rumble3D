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

	bool BoxSphereNarrowAlgorithm::generateContactDataImpl(RigidBody* rbBox, CollisionBox* box,
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
		//glm::vec3 relCentre = box.GetTransform().transformInverse(centre);
		// TODO: test result
		const auto& boxTransform = rbBox->getTransform();
		glm::vec3 relCentre = glm::transpose(boxTransform.getRotation()) *
			(centre - boxTransform.getPosition());

		// Early out check 
		const auto boxDim = box->getHalfSize();

		if(abs(relCentre.x) - sphere->getRadius() > boxDim.x ||
		   abs(relCentre.y) - sphere->getRadius() > boxDim.y ||
		   abs(relCentre.z) - sphere->getRadius() > boxDim.z)
		{
			return false;
		}

		// Clamp each coordinate to the box.
		glm::vec3 closestPt{};

		auto distX = relCentre.x;
		distX = glm::clamp(distX, -boxDim.x, boxDim.x);
		closestPt.x = distX;

		auto distY = relCentre.y;
		distY = glm::clamp(distY, -boxDim.y, boxDim.y);
		closestPt.y = distY;

		auto distZ = relCentre.z;
		distZ = glm::clamp(distZ, -boxDim.z, boxDim.z);
		closestPt.z = distZ;

		// Prüfe, ob ein Kontakt vorliegt:
		const auto distance = glm::length2(closestPt - relCentre);
		if(distance > sphere->getRadius() * sphere->getRadius())
		{
			return false;
		}

		// Erstelle den Kontakt:
		//glm::vec3 closestPtWorld = 
		//	glm::vec3(box.getTransform() * glm::vec4(closestPt, static_cast<real>(1.0f)));

		const auto closestPtWorld = rbBox->getPointInWorldSpace(closestPt);
	

		auto* contact = collisionData.getAvailableContact();
		glm::vec3 tmp = (closestPtWorld - centre);
		tmp = glm::normalize(tmp);
		contact->setContactNormal(tmp);
		contact->setContactPoint(closestPtWorld);
		contact->setPenetration(sphere->getRadius() - sqrt(distance));
		contact->setBodyData(rbBox, rbSphere,
							 collisionData.getFriction(), collisionData.getRestitution());
		return true;
	}
}
