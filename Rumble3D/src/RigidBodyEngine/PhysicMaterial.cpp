#include "R3D/RigidBodyEngine/PhysicMaterial.h"

namespace r3
{
	PhysicMaterial::PhysicMaterial()
	{
		m_mat = PhysicMaterialDef();
	}

	PhysicMaterial::PhysicMaterial(const PhysicMaterialDef& definition)
	{
		m_mat = definition;
	}

	void PhysicMaterial::setFriction(const real friction)
	{
		m_mat.m_friction = friction;
	}

	real PhysicMaterial::getFriction() const
	{
		return m_mat.m_friction;
	}

	void PhysicMaterial::setRestitution(const real restitution)
	{
		m_mat.m_restitution = restitution;
	}

	real PhysicMaterial::getRestitution() const
	{
		return m_mat.m_restitution;
	}

	const PhysicMaterialDef& PhysicMaterial::getMaterialDef() const
	{
		return m_mat;
	}

	PhysicMaterial::~PhysicMaterial()
	= default;

	void PhysicMaterial::init(const PhysicMaterialDef& definition)
	{
		m_mat = definition;
	}
}
