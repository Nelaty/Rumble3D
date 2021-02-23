#include "R3D/RigidBodyEngine/PhysicsMaterial.h"

namespace r3
{
	PhysicsMaterial::PhysicsMaterial()
	{
		m_mat = PhysicsMaterialDef();
	}

	PhysicsMaterial::PhysicsMaterial(const PhysicsMaterialDef& definition)
	{
		m_mat = definition;
	}

	void PhysicsMaterial::setFriction(const real friction)
	{
		m_mat.m_friction = friction;
	}

	real PhysicsMaterial::getFriction() const
	{
		return m_mat.m_friction;
	}

	void PhysicsMaterial::setRestitution(const real restitution)
	{
		m_mat.m_restitution = restitution;
	}

	real PhysicsMaterial::getRestitution() const
	{
		return m_mat.m_restitution;
	}

	const PhysicsMaterialDef& PhysicsMaterial::getMaterialDef() const
	{
		return m_mat;
	}

	void PhysicsMaterial::init(const PhysicsMaterialDef& definition)
	{
		m_mat = definition;
	}
}
