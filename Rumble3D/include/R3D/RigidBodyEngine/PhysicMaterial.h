#pragma once
#include "R3D/Common/Common.h"
#include "R3D/Common/Precision.h"

namespace r3
{
	struct PhysicMaterialDef
	{
		real m_friction{0.0f};
		real m_restitution{1.0f};
	};

	class PhysicMaterial
	{
	public:
		explicit PhysicMaterial();
		explicit PhysicMaterial(const PhysicMaterialDef& definition);
		PhysicMaterial& operator=(const PhysicMaterial&) = default;
		~PhysicMaterial();

		void init(const PhysicMaterialDef& definition);

		void setFriction(real friction);
		real getFriction() const;

		void setRestitution(real restitution);
		real getRestitution() const;

		const PhysicMaterialDef& getMaterialDef() const;

	private:
		PhysicMaterialDef m_mat;
	};
}