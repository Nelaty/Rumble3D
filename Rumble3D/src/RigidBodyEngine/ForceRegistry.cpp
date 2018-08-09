#include "R3D/RigidBodyEngine/ForceRegistry.h"
#include "R3D/RigidBodyEngine/ForceGenerator.h"
#include "R3D/RigidBodyEngine/RigidBody.h"

namespace rum
{
	void ForceRegistry::Remove(RigidBody * rigidBody, ForceGenerator * fg)
	{
		Registry::iterator i = registrations.begin();
		for (; i != registrations.end(); i++)
		{
			if (i->rigidBody == rigidBody && i->forceGenerator == fg)
			{
				registrations.erase(i);
			}
		}
	}
	
	
	void ForceRegistry::Clear()
	{
		registrations.clear();
	}
	
	void ForceRegistry::Add(RigidBody * rigidBody, ForceGenerator * fg)
	{
		ForceRegistrationEntry registration;
		registration.rigidBody = rigidBody;
		registration.forceGenerator = fg;
		registrations.push_back(registration);
	}
	
	
	void ForceRegistry::UpdateForces(real duration)
	{
		for (ForceRegistrationEntry i : registrations)
		{
			i.forceGenerator->UpdateForce(i.rigidBody, duration);
		}
	}
}
